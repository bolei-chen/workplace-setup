if exists('g:vscode')
    " VSCode extension
else
    " ordinary Neovim
endif

highlight Cursor guifg=white guibg=black
set guicursor=n-v-c:block-Cursor
let mapleader = ","

call plug#begin()
" Plug 'prabirshrestha/asyncomplete.vim'
" Plug 'prabirshrestha/asyncomplete-lsp.vim'
" Plug 'prabirshrestha/vim-lsp'
" plug 'mattn/vim-lsp-settings'
Plug 'https://github.com/tpope/vim-fugitive'
" Plug 'scrooloose/nerdtree'
" plug 'https://github.com/vim-airline/vim-airline'
" plug 'https://github.com/vim-airline/vim-airline-themes'
Plug 'https://github.com/tpope/vim-surround'
Plug 'https://github.com/michaeljsmith/vim-indent-object'
Plug 'https://github.com/tpope/vim-commentary'
call plug#end()

" if has('syntax')
"     filetype plugin indent on
" endif

" function! s:on_lsp_buffer_enabled() abort
"     setlocal omnifunc=lsp#complete
"     setlocal signcolumn=yes
"     if exists('+tagfunc') | setlocal tagfunc=lsp#tagfunc | endif
"     nmap <buffer> gd <plug>(lsp-definition)
"     nmap <buffer> gs <plug>(lsp-document-symbol-search)
"     nmap <buffer> gS <plug>(lsp-workspace-symbol-search)
"     nmap <buffer> gr <plug>(lsp-references)
"     nmap <buffer> gi <plug>(lsp-implementation)
"     nmap <buffer> gt <plug>(lsp-type-definition)
"     nmap <buffer> <leader>rn <plug>(lsp-rename)
"     nmap <buffer> [g <plug>(lsp-previous-diagnostic)
"     nmap <buffer> ]g <plug>(lsp-next-diagnostic)
"     nnoremap <buffer> <expr><c-j> lsp#scroll(+4)
"     nnoremap <buffer> <expr><c-k> lsp#scroll(-4)

"     let g:lsp_format_sync_timeout = 1000
"     autocmd! BufWritePre *.hs,*.cpp,*.java,*.py,*.c call execute('LspDocumentFormatSync')

"     " refer to doc to add more commands
" endfunction


" augroup lsp_install
"     au!
"     " call s:on_lsp_buffer_enabled only for languages that has the server registered.
"     autocmd User lsp_buffer_enabled call s:on_lsp_buffer_enabled()
" augroup END

" let g:lsp_document_highlight_enabled = 0
syntax off
set nobackup
set nowritebackup
" set updatetime=300
set encoding=utf-8
set number relativenumber
set splitbelow splitright
set clipboard+=unnamed

" auto completion
set wildmenu

" disable auto commenting
autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o

" spell check mapping
map <leader>sc :setlocal spell! spelllang=en_us<CR>

:highlight LineNr ctermfg=grey

" split navigation setting
map <C-v> <C-w>v
map <C-h> <C-w>h
map <C-j> <C-w>j
map <C-k> <C-w>k
map <C-l> <C-w>l


" tab navigation
map <C-n> :tabn<cr>
map <C-p> :tabp<cr>

" tab thing
set shiftwidth=2
set expandtab
set tabstop=2

" delete all trailing whitespace on save
autocmd BufWritePre * %s/\s\+$//e

" " stuff for airline mode
" let g:airline#extensions#tabline#enabled = 1 " Enable the list of buffers
" let g:airline#extensions#tabline#formatter = 'unique_tail_improved'
" let g:airline#extensions#tabline#left_sep = ' '
" let g:airline#extensions#tabline#left_alt_sep = '|'
" let g:airline_theme='deus'

" mappings for convenience
noremap o o <esc>
noremap O O <esc>
noremap <F1> :NERDTreeToggle <CR>
noremap n nzz
noremap N Nzz
noremap Y y$

" search settings
set incsearch
set nohlsearch
set ignorecase
set smartcase

" search the selected texts in visual mode
vnoremap <silent> * :<C-u>call VisualSelection('', '')<CR>/<C-R>=@/<CR><CR>

