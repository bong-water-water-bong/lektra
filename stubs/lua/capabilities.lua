---@meta
lektra = lektra or {}

--- Table to query capabilities
lektra.capabilities = {}

--- Returns true if lektra is compiled with image support
---@return boolean image_support
lektra.capabilities.image = function () end

--- Returns true if lektra is compiled with synctex support
---@return boolean synctex_support
lektra.capabilities.synctex = function () end

--- Returns true if lektra is compiled with djvu support
---@return boolean djvu_support
lektra.capabilities.djvu = function () end
