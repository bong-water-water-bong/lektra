#include "DispatchType.hpp"
#include "Lektra.hpp"

bool
Lektra::removeLuaEventCallback(DispatchType type, int callbackRef) noexcept
{
    auto it = m_lua_event_dispatcher.find(type);
    if (it == m_lua_event_dispatcher.end())
        return false;

    auto &callbacks   = it->second;
    auto originalSize = callbacks.size();

    callbacks.erase(
        std::remove_if(callbacks.begin(), callbacks.end(),
                       [this, callbackRef](const LuaCallback<Lektra> &cb)
    {
        if (cb.ref == callbackRef)
        {
            luaL_unref(m_L, LUA_REGISTRYINDEX, cb.ref);
            return true;
        }
        return false;
    }),
        callbacks.end());

    return callbacks.size() < originalSize;
}

void
Lektra::initLuaEventDispatcher() noexcept
{
    lua_newtable(m_L);

    // lektra.event.register(EventType, callback) -> handle (int)
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        DispatchType type = static_cast<DispatchType>(luaL_checkinteger(L, 1));
        luaL_checktype(L, 2, LUA_TFUNCTION);

        int callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);

        auto *self
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        self->addEventListener(type, callbackRef, false,
                               [L = self->m_L, callbackRef](Lektra *lektra)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef);
            lua_pushlightuserdata(L, lektra);
            if (lua_pcall(L, 1, 0, 0) != LUA_OK)
            {
                const char *errorMsg = lua_tostring(L, -1);
                fprintf(stderr, "Lua error in event callback: %s\n", errorMsg);
                lua_pop(L, 1);
            }
        });

        lua_pushinteger(L, callbackRef);
        return 1;
    }, 1);

    lua_setfield(m_L, -2, "register");

    // lektra.event.unregister(EventType, handle)
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        DispatchType type = static_cast<DispatchType>(luaL_checkinteger(L, 1));
        int handle        = luaL_checkinteger(L, 2);

        auto *self
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        self->removeLuaEventCallback(type, handle);

        return 0;
    }, 1);

    lua_setfield(m_L, -2, "unregister");

    // lektra.event.once(EventType, callback)
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        DispatchType type = static_cast<DispatchType>(luaL_checkinteger(L, 1));
        luaL_checktype(L, 2, LUA_TFUNCTION);

        int callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);

        auto *self
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        self->addEventListener(type, callbackRef, true,
                               [L = self->m_L, callbackRef](Lektra *lektra)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, callbackRef);
            lua_pushlightuserdata(L, lektra);
            if (lua_pcall(L, 1, 0, 0) != LUA_OK)
            {
                const char *errorMsg = lua_tostring(L, -1);
                fprintf(stderr, "Lua error in event callback: %s\n", errorMsg);
                lua_pop(L, 1);
            }
            // Ref is freed by dispatchLuaEvent after all once-callbacks fire
        });

        lua_pushinteger(L, callbackRef);
        return 1;
    }, 1);
    lua_setfield(m_L, -2, "once");

    // lektra.event.EventType enum (excludes COUNT sentinel)
    lua_newtable(m_L);

    for (int event = 0; event < static_cast<int>(DispatchType::COUNT); ++event)
    {
        lua_pushinteger(m_L, event);
        lua_setfield(m_L, -2,
                     dispatchTypeToString(static_cast<DispatchType>(event))
                         .toStdString()
                         .c_str());
    }
    lua_setfield(m_L, -2, "EventType");

    // lektra.event.count(EventType) -> int
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        DispatchType type = static_cast<DispatchType>(luaL_checkinteger(L, 1));
        auto *self
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        auto it = self->m_lua_event_dispatcher.find(type);
        if (it == self->m_lua_event_dispatcher.end())
        {
            lua_pushinteger(L, 0);
            return 1;
        }

        lua_pushinteger(L, it->second.size());
        return 1;
    }, 1);
    lua_setfield(m_L, -2, "count");

    lua_setfield(m_L, -2, "event");
}

void
Lektra::dispatchLuaEvent(DispatchType type) noexcept
{
    // Copy so callbacks can safely call unregister without invalidating
    // iteration
    auto callbacks = m_lua_event_dispatcher[type];
    for (const auto &callback : callbacks)
        callback.invoker(this);

    // Remove and free any once-callbacks that just fired
    auto &live = m_lua_event_dispatcher[type];
    live.erase(std::remove_if(live.begin(), live.end(),
                              [this](const LuaCallback<Lektra> &cb)
    {
        if (cb.is_once)
        {
            luaL_unref(m_L, LUA_REGISTRYINDEX, cb.ref);
            return true;
        }
        return false;
    }),
               live.end());
}
