# Path to Oh My Fish install.
set -q XDG_DATA_HOME
  and set -gx OMF_PATH "$XDG_DATA_HOME/omf"
  or set -gx OMF_PATH "$HOME/.local/share/omf"

# Load Oh My Fish configuration.
source $OMF_PATH/init.fish
alias mpv="mpv --force-window --idle --hwdec -v"
alias config='/usr/bin/git --git-dir=$HOME/.cfg/ --work-tree=$HOME'

