#include "TDD-nix-build.hpp"

#include "FetchWidgetManager.hpp"
#include "BuildWidgetManager.hpp"
#include "FetchWidget.hpp"
#include "BuildWidget.hpp"
#include "TerminalWidget.hpp"
#include "WindowManager.hpp"

const std::string alphanum =
    "0123456789"
    "abcdefghijklmnopqrstuvwxyz";

std::string randomString(unsigned int size)
{
    std::string str;
    for(unsigned int i = 0; i < size; ++i) {
        str += alphanum[rand()%alphanum.size()];
    }
    return  str;
}

NixBuild::NixBuild() {
    srand(10);
    m.push_back("acpi-1.7");
    m.push_back("aescrypt-3.0.9");
    m.push_back("anki-2.0.22");
    m.push_back("aria2-1.18.1");
    m.push_back("audacity-2.0.5");
    m.push_back("autossh-1.4c");
    m.push_back("basket-1.81");
    m.push_back("bc-1.06");
    m.push_back("blender-2.70");
    m.push_back("brickd-1.0.11");
    m.push_back("brickv-1.1.14");
    m.push_back("bsddb3-6.0.1");
    m.push_back("byobu-5.68");
    m.push_back("calibre-1.31.0");
    m.push_back("davfs2-1.4.7");
    m.push_back("ddd-3.3.12");
    m.push_back("dhex-0.68");
    m.push_back("duplicity-0.6.23");
    m.push_back("elinks-0.12pre6");
    m.push_back("emacs-24.3");
    m.push_back("encfs-1.7.4");
    m.push_back("env-opencv-fishing");
    m.push_back("env-srmg");
    m.push_back("evopedia-0.4.2");
    m.push_back("ffmpeg-2.2.1");
    m.push_back("file-5.17");
    m.push_back("gajim-0.15.4");
    m.push_back("gdb-7.7");
    m.push_back("gimp-2.8.10");
    m.push_back("git-1.9.2");
    m.push_back("glxinfo-8.1.0");
    m.push_back("gnupg-2.0.22");
    m.push_back("gnuplot-4.6.3");
    m.push_back("gobby-0.4.94");
    m.push_back("gpgme-1.4.3");
    m.push_back("gqview-2.1.5");
    m.push_back("htop-1.0.2");
    m.push_back("ikiwiki-3.20140227");
    m.push_back("inkscape-0.48.4");
    m.push_back("inotify-tools-3.13");
    m.push_back("iotop-0.6");
    m.push_back("iperf-2.0.5");
    m.push_back("irssi-0.8.15");
    m.push_back("kdiff3-0.9.97");
    m.push_back("keepassx-2.0alpha5");
    m.push_back("ktorrent-4.3.1");
    m.push_back("libmcrypt-2.5.8");
    m.push_back("libnoise-1.0.0");
    m.push_back("libreoffice-4.0.5.2");
    m.push_back("lightning-1.2c");
    m.push_back("lsof-4.87");
    m.push_back("mcrypt-2.6.8");
    m.push_back("mplayer-1.1");
    m.push_back("nmap-6.40");
    m.push_back("openssl-1.0.1g");
    m.push_back("p7zip-9.20.1");
    m.push_back("patchelf-0.8");
    m.push_back("pavucontrol-2.0");
    m.push_back("phantomjs-1.9.7-4");
    m.push_back("picocom-1.7");
    m.push_back("pinentry-0.8.3");
    m.push_back("psi-0.15-rc3");
    m.push_back("pwgen-2.06");
    m.push_back("qgit-2.5");
    m.push_back("rdiff-backup-1.3.3");
    m.push_back("rsync-3.1.0");
    m.push_back("rtmpdump-2.4");
    m.push_back("seahorse-3.10.2");
    m.push_back("send_udp-1.0.0");
    m.push_back("skype-4.2.0.11");
    m.push_back("smokegen-4.12.4");
    m.push_back("sox-14.4.1");
    m.push_back("sqlite-3.8.0.2-interactive");
    m.push_back("sshfs-fuse-2.5");
    m.push_back("stardict-3.0.3");
    m.push_back("subversion-1.8.8");
    m.push_back("thunderbird-17.0.11esr");
    m.push_back("tig-1.2.1");
    m.push_back("tightvnc-1.3.10");
    m.push_back("timidity-2.13.0");
    m.push_back("tmux-1.8");
    m.push_back("unrar-5.1.2");
    m.push_back("unzip-6.0");
    m.push_back("vim_configurable-7.4.23");
    m.push_back("vlc-2.1.4");
    m.push_back("wgetpaste-2.23");
    m.push_back("which-2.20");
    m.push_back("wireshark-1.11.2");
    m.push_back("xbmc-12.3");
    m.push_back("xclip-0.12");
    m.push_back("xev-1.2.1");
    m.push_back("xinput-1.6.1");
    m.push_back("xset-1.2.3");
    m.push_back("xz-5.0.5");
    m.push_back("youtube-dl-2014.04.02");
    m.push_back("zip-3.0");

    for(int i=0; i < 30; ++i) {
        std::string n ="/nix/store/";
        n+= randomString(44);
        n+= "-";
        n+= m[rand()%m.size()];
        n+= "-";
        n+= ".nar.xz";
        float f =  0.01f*(rand()%103);
        if (f > 1.0)
            f = 1.0f;
        if (f < 0)
            f = 0.0f;
        FetchWidgetManager::Instance()->add(new FetchWidget(n, f, 33234045));
    }

    for(int i=0; i < 40; ++i) {
        std::string n = "/nix/store/";
        n+= randomString(44);
        n+= "-";
        n+= m[rand()%m.size()];
        BuildWidgetManager::Instance()->add(new BuildWidget(n, "installationPhase 5/8"));
    }

    AdvancedStringContainer s;
    s << AdvancedString("building Nix...\n");
    s << AdvancedString("these derivations will be ") << AdvancedString("built", COLOR_MAGENTA) << AdvancedString(":\n");
    //FIXME implement this
//     for(int i=0; i < BuildWidgetManager::Instance()->m_widgets; i++) {
//       s <<  AdvancedString(BuildWidgetManager::Instance()->m_widgets[i]->name(), COLOR_MAGENTA) << "\n";
//     }

    s << AdvancedString("these paths will be ") << AdvancedString("fetched", COLOR_GREEN) << AdvancedString(" (") << AdvancedString("40.1", COLOR_YELLOW) << AdvancedString(" Mib download, ") << AdvancedString("201.66", COLOR_YELLOW) << AdvancedString(" Mib unpacked):\n");
    //FIXME implement this
    //     for(int i=0; i < BuildWidgetManager::Instance()->m_widgets; i++) {
//         s << AdvancedString("  /nix/store/0yzz6p08k1sgpdb63c0wx48vx0yc51g6-") << AdvancedString("bzip2-1.0.6\n", COLOR_GREEN);
//     }

    TerminalWidget::Instance()->append(s);
}


void NixBuild::tick() {
  //FIXME emulate updates on objects like download progress, bandwidth changes and after 100% remove them from the list and write a log entry
  
}
