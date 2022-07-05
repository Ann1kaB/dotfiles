# Path to Oh My Fish install.
set -q XDG_DATA_HOME
  and set -gx OMF_PATH "$XDG_DATA_HOME/omf"
  or set -gx OMF_PATH "$HOME/.local/share/omf"
set PATH $PATH /home/annika/.local/bin /opt/piavpn/bin/ /opt/Ryzen\ Controller/
set -x EDITOR nvim
#set -x CC ccache clang
#set -x CXX ccache clang++
#set -x CFLAGS '-O3 -pipe -flto=thin -fno-plt'
#set -x CXXFLAGS '-O3 -pipe -flto=thin -fno-plt'
#set -x LDFLAGS '-fuse-ld=lld -Wl,--thinlto-cache-dir=/home/hyperkvm/.local/share/ccache/clang'
#set -x AS llvm-as
#set -x NM llvm-nm
#set -x LD ld.lld
#set -x CPP clang-cpp
#set -x RANLIB llvm-ranlib
#set -x OBJCOPY llvm-objcopy
#set -x OBJDUMP llvm-objdump 
#set -x STRIP llvm-strip
#set -x READELF llvm-readelf
#set -x AR llvm-ar

# Load Oh My Fish configuration.
#source $OMF_PATH/init.fish
alias mpv="mpv --force-window --idle --hwdec -v"
alias config='/usr/bin/git --git-dir=$HOME/.cfg/ --work-tree=$HOME'
#alias prime-run='__NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia'
alias amd-run="VK_ICD_FILENAMES=/usr/share/vulkan/icd.d/radeon*"
#alias startx='startx; ./.prime-switch'
#alias xbps-src='~/git/void-packages/xbps-src'
#alias firefox='LIBVA_DRIVER_NAME=nvidia MOZ_DISABLE_RDD_SANDBOX=1 /usr/bin/firefox'
alias firefox='MOZ_DISABLE_RDD_SANDBOX=1 /usr/bin/firefox'
#alias dolphin-emu='prime-run /usr/bin/dolphin-emu'
alias ryzen-controller="sudo /opt/Ryzen\ Controller/ryzen-controller --no-sandbox"
