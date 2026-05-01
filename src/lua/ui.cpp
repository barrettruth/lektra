#include "Lektra.hpp"

#include <QMessageBox>

void
Lektra::initLuaUI() noexcept
{
    lua_newtable(m_L); // lektra.ui

    // lektra.ui.show_message(title, message, type)
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        const char *title   = luaL_checkstring(L, 1);
        const char *message = luaL_checkstring(L, 2);
        const char *type    = luaL_optstring(L, 3, "info");

        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        if (strcmp(type, "info") == 0)
            QMessageBox::information(lektra, title, message);
        else if (strcmp(type, "warning") == 0)
            QMessageBox::warning(lektra, title, message);
        else if (strcmp(type, "error") == 0)
            QMessageBox::critical(lektra, title, message);
        else
            return luaL_error(L, "Invalid message type: %s", type);

        return 0; // Number of return values
    }, 1);
    lua_setfield(m_L, -2, "show_message");

    // lektra.ui.input(title, message)
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        const char *title   = luaL_checkstring(L, 1);
        const char *message = luaL_checkstring(L, 2);

        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        bool ok;
        const QString input = QInputDialog::getText(
            lektra, title, message, QLineEdit::Normal, QString(), &ok);
        if (ok)
        {
            lua_pushstring(L, input.toStdString().c_str());
            return 1; // Number of return values
        }
        else
        {
            lua_pushnil(L);
            return 1; // Number of return values
        }
    }, 1);
    lua_setfield(m_L, -2, "input");

    lua_setfield(m_L, -2, "ui");
}
