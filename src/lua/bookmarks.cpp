#include "Lektra.hpp"

void
Lektra::initLuaBookmarks() noexcept
{
    lua_newtable(m_L);

    // lektra.bookmarks.list() -> (Bookmark){ id=..., filepath=...,
    // location=..., created=... }
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        auto &bm = lektra->m_bookmark_manager;

        lua_newtable(L);
        int idx = 1;
        for (const auto &bk : bm.bookmarks())
        {
            lua_newtable(L);
            std::string created = bk.createdAt().toString().toStdString();
            std::string id      = bk.id().toStdString();

            lua_pushstring(L, id.c_str());
            lua_setfield(L, -2, "id");

            lua_pushstring(L, bk.filePath().toUtf8().constData());
            lua_setfield(L, -2, "file_path");

            {
                auto loc = bk.location();
                lua_pushinteger(L, loc.pageno + 1);
                lua_setfield(L, -2, "pageno");
                lua_pushnumber(L, loc.x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, loc.y);
                lua_setfield(L, -2, "y");
            }

            lua_pushstring(L, created.c_str());
            lua_setfield(L, -2, "created");

            lua_rawseti(L, -2, idx++); // for use in the table
        }

        return 1;
    }, 1);
    lua_setfield(m_L, -2, "list");

    lua_setfield(m_L, -2, "bookmarks");
}
