---@meta

lektra = lektra or {}
lektra.tabs = {}

---@class Tab
local Tab = {}

--- Returns the unique identifier for the tab.
---@return integer|nil ID The ID of the tab.
function Tab:id() end

--- Close the tab
function Tab:close() end

--- Returns the title of the tab.
---@return string title The title of the tab.
function Tab:title() end

--- Returns the View object associated with the tab.
---@return View view The View object for the tab.
function Tab:view() end

--- Returns the index of the tab (0-based).
---@return integer index The index of the tab.
function Tab:index() end

-- ###########################################################

--- Closes the tab with the specified unique identifier.
---@param id integer The index of the tab to close.
lektra.tabs.close = function(id) end

--- Switches to the tab with the specified unique identifier.
---@param id integer The index of the tab to close.
lektra.tabs.goto = function(id) end

--- Switches to the last active tab.
lektra.tabs.last = function() end

--- Switches to the first tab.
lektra.tabs.first = function() end

--- Switches to the next tab.
lektra.tabs.next = function() end

--- Switches to the previous tab.
lektra.tabs.prev = function() end

--- Moves the current tab to the right.
lektra.tabs.move_right = function() end

--- Moves the current tab to the left.
lektra.tabs.move_left = function() end

--- Returns the number of open tabs.
--- @return integer
lektra.tabs.count = function() end

--- Returns the Tab object for the current tab.
---@return Tab
lektra.tabs.current = function() end

--- Returns a table of tab objects
--- @return Tab[] tabs List of Tab objects
lektra.tabs.list = function() end

--- Returns the stable unique identifier for a tab index (0-based).
---@param index integer
---@return string id
lektra.tabs.get_id = function(index) end
