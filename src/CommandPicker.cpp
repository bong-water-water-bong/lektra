#include "CommandPicker.hpp"

#include "Picker.hpp"

CommandPicker::CommandPicker(const Config::CommandPalette &config,
                             const std::vector<Command> &commands,
                             const ShortcutMap &shortcuts,
                             QWidget *parent) noexcept
    : Picker(config, parent), m_config(config), m_commands(commands),
      m_shortcuts(shortcuts)
{
    QList<Column> cols;
    cols.append({.header    = "Command",
                 .stretch   = 1,
                 .alignment = Qt::AlignLeft | Qt::AlignVCenter});
    if (m_config.description)
        cols.append({.header = "Description", .stretch = 2});
    if (m_config.show_shortcuts)
        cols.append({.header    = "Shortcut",
                     .stretch   = 0,
                     .alignment = Qt::AlignRight | Qt::AlignVCenter});
    setScrollbarEnabled(m_config.vscrollbar);
    setColumns(cols);

    setStructureMode(StructureMode::Flat);

    setPrompt(config.prompt);
}

QList<Picker::Item>
CommandPicker::collectItems()
{
    QList<Item> items;
    items.reserve(static_cast<int>(m_commands.size()));

    for (size_t i = 0; i < m_commands.size(); ++i)
    {
        const Command &cmd = m_commands[i];
        QList<QString> cols;
        cols.append(cmd.name);
        if (m_config.description)
            cols.append(cmd.description);
        if (m_config.show_shortcuts)
            cols.append(m_shortcuts.value(cmd.name).join(", "));
        items.push_back(
            {.columns = cols, .data = static_cast<quint64>(i), .children = {}});
    }
    return items;
}

void
CommandPicker::onItemAccepted(const Item &item)
{
    const size_t i = item.data.toULongLong();
    if (m_commands.at(i).action)
        m_commands.at(i).action({});
}
