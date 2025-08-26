require("nvchad.configs.lspconfig").defaults()

local servers = { "clangd", "rust_analyzer", "postgres_lsp" }

vim.lsp.config.clangd = {
    cmd = {
        'clangd',
        '--clang-tidy',
        '--background-index',
        '--offset-encoding=utf-8',
        '--header-insertion=never',
        '--function-arg-placeholders=false',
        '--limit-results=10',
        '--limit-references=5'
    },
    root_markers = { '.clangd', 'compile_commands.json' },
    filetypes = { 'c', 'cpp', 'h', 'hpp' },
}

vim.lsp.enable(servers)
-- read :h vim.lsp.config for changing options of lsp servers 
