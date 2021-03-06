# Bash RC for etna.physics.purdue.edu 

# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

#source ~/root/bin/thisroot.sh
#source ~/local/share/root/bin/thisroot.sh

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# some more ls aliases
#alias ll='ls -alF'
#alias la='ls -A'
#alias l='ls -CF'

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if [ -f /etc/bash_completion ] && ! shopt -oq posix; then
    . /etc/bash_completion
fi


#-----------------------------------ye---------------
# General ENV
#--------------------------------------------------
export CLICOLOR=1
export LSCOLORS=ExFxCxDxBxegedabagacad
export CVSEDITOR=vim
export PATH=$HOME/local/bin:$PATH
export PATH=/opt/local/bin:/opt/local/sbin:$PATH #for MacPorts
export LESS='-R'
export LESSOPEN='|~/.sys/lessfilter.sh %s' 

#--------------------------------------------------
# General Aliases
#--------------------------------------------------
alias l="ls"
alias ll="l -lh"
alias lsd="l -d */"
alias p="pwd"
alias rl="root -l" 
alias rm~="rm *~"
alias ..='cd ..'
alias setroot6="source ~/local/share/root6/bin/thisroot.sh"
alias setroot5="source ~/local/share/root5/bin/thisroot.sh"
#--------------------------------------------------
# Functions 
#--------------------------------------------------
et() {
    echo "Recursively generating TAGS for *.cc *.h *.py ..."
    find . -name "*.cc" -print -or -name "*.h" -print  -or -name "*.py" -print | xargs etags
}

sl() {
    if [ -z "$1" ]; then
	echo "[rcac]    hep.rcac.purdue.edu"
	echo "[cern]    lxplus.cern.ch"
	read menu 
    else
	menu=$1
    fi

    export sl_rcac=shi210@hep.rcac.purdue.edu 
    export sl_cern=xshi@lxplus.cern.ch

    case $menu in 
	rcac) ssh -Y shi210@hep.rcac.purdue.edu 
	    ;;

	cern) ssh -Y xshi@lxplus.cern.ch
	    ;;
    esac
}


#--------------------------------------------------
# CMSPXL ENV
#--------------------------------------------------
# This setup must be issued in the cmspxl directory. 
#export PATH=$PWD/bin:$PATH
#export MANPATH=$PWD/doc:$MANPATH 
# pwd_=$PWD 
# cd ~/cmspxl
# . setup.sh
# cd $pwd_ 

export SUBSERVER="127.0.0.1:12334"

setpxl() {
    if [ -z "$1" ]; then
	echo "Please specify the version: [1.0]" 
	return 
    fi; 

    if [ "$1" = 1.2 ]; then
	setroot5 
	export PATH=/home/purduepix/cmspxl/v2015.04/bin:/home/purduepix/pxar/v2015.04/bin:/home/purduepix/pxar/v2015.04/main:/home/purduepix/elComandante/v1.1/subsystem:/home/purduepix/elComandante/v1.1/elComandante:$PATH 
    fi;

    if [ "$1" = 1.1 ]; then
	setroot5 
	export PATH=/home/purduepix/cmspxl/v2015.04/bin:/home/purduepix/pxar/pxar_crosscalibrate/bin:/home/purduepix/pxar/pxar_crosscalibrate/main:/home/purduepix/elComandante/v1.1/subsystem:/home/purduepix/elComandante/v1.1/elComandante:$PATH 
    fi;

    if [ "$1" = 1.0 ]; then
	setroot5 
	export PATH=/home/purduepix/cmspxl/v2015.01/bin:/home/purduepix/pxar/v2014.11/bin:/home/purduepix/pxar/v2014.11/main:/home/purduepix/elComandante/v1.0/subsystem:/home/purduepix/elComandante/v1.0/elComandante:$PATH 
    fi;

    echo "Using the following binnary: "
    which root 
    which pXar
    which mkConfig
    which drawMod
    which drawIV
    which subserver
    which client
    which el_comandante.py
}

# Set the default env 
setpxl 1.2 
