#include "Lektra.hpp"

#include <QMessageBox>

void
Lektra::executeLuaCode(const QString &code) noexcept
{
    if (!m_L)
        return;

    const int base = lua_gettop(m_L);
    const QByteArray codeUtf8 = code.toUtf8();

    if (luaL_loadstring(m_L, codeUtf8.constData()) != LUA_OK)
    {
        qWarning() << "Failed to load Lua code:" << lua_tostring(m_L, -1);
        lua_settop(m_L, base);
        return;
    }

    if (lua_pcall(m_L, 0, 0, 0) != LUA_OK)
    {
        qWarning() << "Failed to execute Lua code:" << lua_tostring(m_L, -1);
        lua_settop(m_L, base);
    }
}

void
Lektra::initLua() noexcept
{
    m_L = luaL_newstate();

    luaL_openlibs(m_L);

    lua_newtable(m_L); // "lektra" global table for organization

    // Register functions
    initLuaOpt();
    initLuaCmd();
    initLuaUI();
    initLuaTabs();
    initLuaEventDispatcher();
    initLuaView();
    initLuaKeymaps();
    initLuaMousemaps();
    initLuaUtils();

    lua_setglobal(m_L, "lektra");

    loadLuaConfig();
}
