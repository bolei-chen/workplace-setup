# change the data shown.
PROMPT="%n@ %/ %# "

# set vi as default editor.
set o -vi

# change path from bash to zsh.
export PATH="$HOME/bin:/usr/local/bin:$PATH"

# anaconda path
export PATH=$PATH:$HOME/anaconda3/bin

export PATH=$PATH:$HOMR/.local/bin

# maven path
export M2_HOME="/Users/pankaj/Downloads/apache-maven-3.9.0"
export PATH="${M2_HOME}/bin:${PATH}"

# path to installation.
export ZSH="$HOME/.oh-my-zsh"

# https://github.com/ohmyzsh/ohmyzsh/wiki/Themes

# case sensitive completion.
CASE_SENSITIVE="true"

# just remind me to update when it's time
zstyle ':omz:update' mode reminder

DISABLE_MAGIC_FUNCTIONS="true"

DISABLE_LS_COLORS="true"

ENABLE_CORRECTION="true"

DISABLE_UNTRACKED_FILES_DIRTY="true"

plugins=(git zsh-autosuggestions z sudo copyfile macos copypath web-search)


# user configuration

# export MANPATH="/usr/local/lei:$MANPATH"

# set language environment
export LANG=en_US.UTF-8

# Preferred editor for local and remote sessions
# if [[ -n $SSH_CONNECTION ]]; then
#   export EDITOR='nvim'
# else
#   export EDITOR='mvim'
# fi

# Press c to clear the terminal screen.
alias c='clear'
alias ls='ls --color=none'

#[ -f "/Users/lei/.ghcup/env" ] && source "/Users/lei/.ghcup/env" # ghcup-env
[ -f "/Users/lei/.ghcup/env" ] && source "/Users/lei/.ghcup/env" # ghcup-env

source $ZSH/oh-my-zsh.sh

# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/Users/lei/anaconda3/bin/conda' 'shell.zsh' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/Users/lei/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/Users/lei/anaconda3/etc/profile.d/conda.sh"
    else
        export PATH="/Users/lei/anaconda3/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<

source /Users/lei/.bash_profile
