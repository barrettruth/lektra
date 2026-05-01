#include "Lektra.hpp"

// Options for the open() API function, parsed from the Lua table passed by the
// user.
struct OpenFileopts
{
    bool dwim       = false;
    bool vsplit     = false;
    bool hsplit     = false;
    bool new_window = false;
};

// Read an optional boolean field from a Lua table at stack index `table_idx`.
static void
read_bool_field(lua_State *L, int table_idx, const char *field, bool &out)
{
    lua_getfield(L, table_idx, field);
    if (lua_isboolean(L, -1))
        out = lua_toboolean(L, -1);
    lua_pop(L, 1);
}

static OpenFileopts
read_open_file_opts(lua_State *L, int idx)
{
    OpenFileopts opts;
    if (lua_isnoneornil(L, idx))
        return opts;
    if (!lua_istable(L, idx))
    {
        luaL_error(L, "open: 'opts' must be a table, got %s",
                   luaL_typename(L, idx));
        return opts;
    }
    read_bool_field(L, idx, "dwim", opts.dwim);
    read_bool_field(L, idx, "vsplit", opts.vsplit);
    read_bool_field(L, idx, "hsplit", opts.hsplit);
    read_bool_field(L, idx, "new_window", opts.new_window);
    return opts;
}

static void
initDocAPI(lua_State *L, Lektra *lektra) noexcept
{
    // -------------------------------------------
    // lektra.api.current_doc_id()
    lua_pushlightuserdata(L, lektra);
    lua_pushcclosure(L, [](lua_State *L) -> int
    {
        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));
        auto *doc = lektra->currentDocument();
        if (!doc)
        {
            lua_pushnil(L);
            return 1;
        }
        const DocumentView::Id id = doc->id();
        if (id)
            lua_pushinteger(L, id);
        else
            lua_pushnil(L);
        return 1;
    }, 1);
    lua_setfield(L, -2, "current_doc_id");

    // ------------------------------------------
    // lektra.api.open(file, [doc_id], [callback], [opts])
    lua_pushlightuserdata(L, lektra);
    lua_pushcclosure(L, [](lua_State *L) -> int
    {
        const char *file        = nullptr;
        DocumentView::Id doc_id = DocumentView::Id();
        int func_ref            = LUA_NOREF;
        OpenFileopts opts;

        if (lua_istable(L, 1))
        {
            // ── Table form: open({ file=, doc_id=, callback=, opts={} }) ──
            lua_getfield(L, 1, "file");
            if (!lua_isstring(L, -1))
                return luaL_error(L, "open: 'file' field must be a string");
            file = lua_tostring(L, -1);
            // leave on stack so pointer stays valid

            lua_getfield(L, 1, "doc_id");
            if (lua_isinteger(L, -1))
                doc_id = static_cast<DocumentView::Id>(lua_tointeger(L, -1));
            lua_pop(L, 1);

            lua_getfield(L, 1, "callback");
            if (!lua_isnoneornil(L, -1))
            {
                if (!lua_isfunction(L, -1))
                    return luaL_error(
                        L, "open: 'callback' must be a function, got %s",
                        luaL_typename(L, -1));
                // already on top — ref it directly, no pushvalue needed
                func_ref = luaL_ref(L, LUA_REGISTRYINDEX);
            }
            else
                lua_pop(L, 1);

            lua_getfield(L, 1, "opts");
            opts = read_open_file_opts(L, lua_gettop(L));
            lua_pop(L, 1);
        }
        else if (lua_isstring(L, 1))
        {
            // ── Positional form: open(file, [doc_id], [callback], [opts])
            file = luaL_checkstring(L, 1);

            if (!lua_isnoneornil(L, 2))
                doc_id = static_cast<DocumentView::Id>(luaL_checkinteger(L, 2));

            if (!lua_isnoneornil(L, 3))
            {
                if (!lua_isfunction(L, 3))
                    return luaL_error(
                        L, "open: argument 3 must be a function, got %s",
                        luaL_typename(L, 3));
                lua_pushvalue(L, 3);
                func_ref = luaL_ref(L, LUA_REGISTRYINDEX);
            }

            opts = read_open_file_opts(L, 4);
        }
        else
        {
            return luaL_error(
                L, "open: expected string or table as first argument, got %s",
                luaL_typename(L, 1));
        }

        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        CallbackFn callback = nullptr;
        if (func_ref != LUA_NOREF)
        {
            callback = [L, func_ref, doc_id]()
            {
                lua_rawgeti(L, LUA_REGISTRYINDEX, func_ref);
                lua_pushinteger(L, doc_id);
                if (lua_pcall(L, 1, 0, 0) != LUA_OK)
                {
                    qWarning() << "open callback error:" << lua_tostring(L, -1);
                    lua_pop(L, 1);
                }
                luaL_unref(L, LUA_REGISTRYINDEX, func_ref);
            };
        }

        const QString path = QString::fromUtf8(file);
        if (opts.dwim)
            lektra->OpenFileDWIM(path, callback);
        else if (opts.vsplit)
            lektra->OpenFileVSplit(path, callback);
        else if (opts.hsplit)
            lektra->OpenFileHSplit(path, callback);
        else if (opts.new_window)
            lektra->OpenFileInNewWindow(path, callback);
        else
            lektra->OpenFileInNewTab(path, callback);

        return 0;
    }, 1);
    lua_setfield(L, -2, "open");

    // ------------------------------------------
    // lektra.api.close(doc_id)
    lua_pushlightuserdata(L, lektra);

    lua_pushcclosure(L, [](lua_State *L) -> int
    {
        int doc_id = -1;
        if (!lua_isnoneornil(L, 1))
            doc_id = luaL_checkinteger(L, 1);

        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        lektra->CloseFile(doc_id);

        return 0;
    }, 1);
    lua_setfield(L, -2, "close");

    // ------------------------------------------
    // lektra.api.hsplit(doc_id)
    lua_pushlightuserdata(L, lektra);
    lua_pushcclosure(L, [](lua_State *L) -> int
    {
        int doc_id = -1;
        if (!lua_isnoneornil(L, 1))
            doc_id = luaL_checkinteger(L, 1);

        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        DocumentView *new_view = lektra->HSplit(doc_id);
        if (new_view)
            lua_pushlightuserdata(L, new_view);
        else
            lua_pushnil(L);
        return 1;
    }, 1);
    lua_setfield(L, -2, "hsplit");

    // ------------------------------------------
    // lektra.api.vsplit(doc_id)
    lua_pushlightuserdata(L, lektra);
    lua_pushcclosure(L, [](lua_State *L) -> int
    {
        int doc_id = -1;
        if (!lua_isnoneornil(L, 1))
            doc_id = luaL_checkinteger(L, 1);

        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));
        DocumentView *new_view = lektra->VSplit(doc_id);
        if (new_view)
            lua_pushlightuserdata(L, new_view);
        else
            lua_pushnil(L);
        return 1;
    }, 1);
    lua_setfield(L, -2, "vsplit");
}

static void
initCommandAPI(lua_State *L, Lektra *lektra) noexcept
{
    lua_pushlightuserdata(L, lektra);
    lua_pushcclosure(L, [](lua_State *L) -> int
    {
        const char *name = nullptr;
        const char *desc = "";
        int func_idx     = -1;

        if (lua_istable(L, 1))
        {
            // ── Table form: register_command({ name=, callback=, desc=
            // }) ──
            lua_getfield(L, 1, "name");
            if (!lua_isstring(L, -1))
                return luaL_error(L,
                                  "register_command: 'name' must be a string");
            name = lua_tostring(L, -1);
            // leave on stack so pointer stays valid until reg() call
            // below

            lua_getfield(L, 1, "desc");
            if (lua_isstring(L, -1))
                desc = lua_tostring(L, -1);
            // leave on stack for same reason

            lua_getfield(L, 1, "callback");
            if (!lua_isfunction(L, -1))
                return luaL_error(
                    L, "register_command: 'callback' must be a function");
            func_idx = lua_gettop(L); // callback is now at top
        }
        else if (lua_isstring(L, 1))
        {
            // ── Positional form: register_command(name, callback [,
            // desc]) ──
            name = luaL_checkstring(L, 1);
            if (!lua_isfunction(L, 2))
                return luaL_error(L,
                                  "register_command: argument 2 must "
                                  "be a function, got %s",
                                  luaL_typename(L, 2));
            func_idx = 2;
            desc     = luaL_optstring(L, 3, "");
        }
        else
        {
            return luaL_error(
                L, "register_command: expected string or table, got %s",
                luaL_typename(L, 1));
        }

        lua_pushvalue(L, func_idx);
        const int func_ref = luaL_ref(L, LUA_REGISTRYINDEX);

        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));

        lektra->commandManager()->reg(name, desc,
                                      [L, func_ref](const QStringList &args)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, func_ref);
            lua_newtable(L);
            int i = 1;
            for (const auto &arg : args)
            {
                lua_pushstring(
                    L,
                    arg.toUtf8().constData()); // BUG FIX: toStdString()
                lua_rawseti(L, -2, i++);       // + c_str() is an
            } // unnecessary roundtrip
            if (lua_pcall(L, 1, 0, 0) != LUA_OK)
            {
                qWarning() << "register_command error:" << lua_tostring(L, -1);
                lua_pop(L, 1);
            }
        });
        return 0;
    }, 1);
    lua_setfield(L, -2, "register_command");
}

void
Lektra::initLuaAPI() noexcept
{
    lua_newtable(m_L);
#ifndef NDEBUG
    const int top = lua_gettop(m_L);
#endif

    initDocAPI(m_L, this);
    Q_ASSERT(lua_gettop(m_L) == top);

    initCommandAPI(m_L, this);
    Q_ASSERT(lua_gettop(m_L) == top);

    lua_setfield(m_L, -2,
                 "api"); // lektra.api = the table we just built
}
