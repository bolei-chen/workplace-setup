set o -vi 
 
PS1='@\u:/\w# '
HISTTIMEFORMAT="%F %T "
HISTCONTROL=ignoredups
HISTSIZE=2000
HISTFILESIZE=2000
 
# Press c to clear the terminal screen.
alias c='clear'

 # Move to the parent folder.
alias ..='cd ..;pwd'

# Move up two parent folders.
alias ...='cd ../..;pwd'

# Move up three parent folders.
alias ....='cd ../../..;pwd'
 
# Press h to view the bash history.
alias h='history'

# Display the directory structure better.
alias tree='tree --dirsfirst -F'
 
# initialize a github project. 
function git_init() {
    if [ -z "$1" ]; then
        printf "%s\n" "Please provide a directory name.";
    else
        mkdir "$1";
        builtin cd "$1";
        pwd;
        git init;
        touch readme.md .gitignore LICENSE;
        echo "# $(basename $PWD)" >> readme.md
    fi
} 
 

