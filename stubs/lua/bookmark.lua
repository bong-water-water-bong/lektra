---@meta
lektra = lektra or {}
lektra.bookmarks = {}

---@class Bookmark
---@field id integer bookmark uuid
---@field file_path string filepath of the bookmark
---@field pageno integer page number of the bookmark (0-based)
---@field x integer xlocation
---@field y integer ylocation
---@field created string datetime of when the bookmark was created

--- Adds a bookmark
---@param bookmark Bookmark
lektra.bookmarks.add = function (bookmark) end

--- Removes a bookmark with the id `id`
lektra.bookmarks.remove = function(id) end

--- Lists all the bookmarks
---@return Bookmark[] bookmarks list of bookmarks
lektra.bookmarks.list = function() end

--- Goes to the bookmark with the id `id`
---@param id integer
lektra.bookmarks.goto = function(id) end

