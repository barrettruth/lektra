#include "Lektra.hpp"

namespace
{

#define VIEW_METHOD(name, body)                                                \
    {name, [](lua_State *L) -> int                                             \
    {                                                                          \
        auto **view = static_cast<DocumentView **>(                            \
            luaL_checkudata(L, 1, "DocumentViewMetaTable"));                   \
        body                                                                   \
    }}

static const luaL_Reg DocumentViewMethods[]
    = {VIEW_METHOD("close",
                   {
                       if (*view)
                           (*view)->close();
                       return 0;
                   }),
       VIEW_METHOD("pageno",
                   {
                       lua_pushinteger(L, (*view)->pageNo() + 1);
                       return 1;
                   }),
       VIEW_METHOD("goto_page",
                   {
                       if (*view)
                           (*view)->GotoPage(luaL_checkinteger(L, 2) - 1);
                       return 0;
                   }),
       {nullptr, nullptr}};

#undef VIEW_METHOD

static void
registerDocumentView(lua_State *L)
{
    // 1. Create the metatable
    luaL_newmetatable(L, "DocumentViewMetaTable");

    // 2. Set __index to itself
    // This trick means: "if a key isn't in the userdata, look in this
    // metatable"
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    // 3. Register the methods into the metatable
    luaL_setfuncs(L, DocumentViewMethods, 0);

    lua_pop(L, 1); // Pop the metatable
}
} // namespace

// Register the DocumentView* type with lua
void
Lektra::initLuaDocumentView() noexcept
{
    registerDocumentView(m_L);

    lua_newtable(m_L);

    // lektra.view.current() -> id
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));
        auto *currentView = lektra->currentDocument();
        if (currentView)
            lua_pushinteger(L, currentView->id());
        else
            lua_pushnil(L);
        return 1;
    }, 1);
    lua_setfield(m_L, -2, "current");

    // lektra.view.get(id) -> DocumentView or nil
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));
        auto id    = static_cast<DocumentView::Id>(luaL_checkinteger(L, 1));
        auto *view = lektra->get_view_by_id(id);
        if (view)
        {
            auto **ud = static_cast<DocumentView **>(
                lua_newuserdata(L, sizeof(DocumentView *)));
            *ud = view;
            luaL_getmetatable(L, "DocumentViewMetaTable");
            lua_setmetatable(L, -2);
        }
        else
        {
            lua_pushnil(L);
        }
        return 1;
    }, 1);
    lua_setfield(m_L, -2, "get");

    // lektra.view.list(tab_index) -> table of DocumentView
    lua_pushlightuserdata(m_L, this);
    lua_pushcclosure(m_L, [](lua_State *L) -> int
    {
        auto *lektra
            = static_cast<Lektra *>(lua_touserdata(L, lua_upvalueindex(1)));
        auto tab_id    = luaL_checkinteger(L, 1);
        auto container = qobject_cast<DocumentContainer *>(
            lektra->m_tab_widget->widget(tab_id));
        if (!container)
        {
            lua_pushnil(L);
            return 1;
        }
        auto views = container->getAllViews();
        lua_newtable(L);
        int index = 1;
        for (auto *view : views)
        {
            auto **ud = static_cast<DocumentView **>(
                lua_newuserdata(L, sizeof(DocumentView *)));
            *ud = view;
            luaL_getmetatable(L, "DocumentViewMetaTable");
            lua_setmetatable(L, -2);
            lua_rawseti(L, -2, index++);
        }
        return 1;
    }, 1);
    lua_setfield(m_L, -2, "list");

    lua_setfield(m_L, -2, "view");
}
