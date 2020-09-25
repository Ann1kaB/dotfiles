# Path to Oh My Fish install.
set -q XDG_DATA_HOME
  and set -gx OMF_PATH "$XDG_DATA_HOME/omf"
  or set -gx OMF_PATH "$HOME/.local/share/omf"
set PATH $PATH /home/hyperkvm/pkg/bin /home/hyperkvm/pkg/sbin
set -x EDITOR nvim
set -x CC /usr/bin/clang

# Load Oh My Fish configuration.
source $OMF_PATH/init.fish
alias mpv="mpv --force-window --idle --hwdec -v"
alias config='/usr/bin/git --git-dir=$HOME/.cfg/ --work-tree=$HOME'
#alias prime-run='__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia'
alias startx='startx; ./.prime-switch'
