#! /bin/bash

function check() {
    if [ "$?" == "1" ];
    then echo "KO"
    else echo "OK"
    fi
}

echo "graphics.so: "
diff <(./my_nm ~/.froot/lib/libsfml-graphics.so.2.3) <(nm ~/.froot/lib/libsfml-graphics.so.2.3)
check
echo "system.so: "
diff <(./my_nm ~/.froot/lib/libsfml-system.so) <(nm ~/.froot/lib/libsfml-system.so)
check
echo "audio.so: "
diff <(./my_nm ~/.froot/lib/libsfml-audio.so) <(nm ~/.froot/lib/libsfml-audio.so)
check
echo "liblapin.a: "
diff <(./my_nm ~/.froot/lib/liblapin.a) <(nm ~/.froot/lib/liblapin.a)
check
echo "main.o: "
diff <(./my_nm src/main.o) <(nm src/main.o)
check
echo "my_nm: "
diff <(./my_nm my_nm) <(nm my_nm)
check
echo "my_malloc.so: "
diff <(./my_nm ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so) <(nm ~/rendu/PSU/PSU_2016_malloc/libmy_malloc.so)
check
echo "many file: "
diff <(./my_nm my_nm src/main.o ~/.froot/lib/libsfml-network.so ~/.froot/lib/liblapin.a) <(nm my_nm src/main.o ~/.froot/lib/libsfml-network.so ~/.froot/lib/liblapin.a)
check
echo "double liblapin.a: "
diff <(./my_nm ~/.froot/lib/liblapin.a ~/.froot/lib/liblapin.a) <(nm ~/.froot/lib/liblapin.a ~/.froot/lib/liblapin.a)
check
echo "32bit: "
diff <(./my_nm ~/test/trash/obj32) <(nm ~/test/trash/obj32)
check
echo "/usr/lib64: "
diff <(./my_nm /usr/lib64/libsamba-credentials.so /usr/lib64/libsamba-errors.so /usr/lib64/libsamba-hostconfig.so /usr/lib64/libsamba-passdb.so /usr/lib64/libsamba-policy.so /usr/lib64/libsamba-util.so /usr/lib64/libsamdb.so /usr/lib64/libsamplerate.so /usr/lib64/libsane.so /usr/lib64/libsasl2.so /usr/lib64/libsbc.so /usr/lib64/libschroedinger-1.0.so /usr/lib64/libseccomp.so /usr/lib64/libsecret-1.so /usr/lib64/libserialize-f5a209a9.so /usr/lib64/libsfml-audio.so /usr/lib64/libsfml-graphics.so /usr/lib64/libsfml-network.so /usr/lib64/libsfml-system.so /usr/lib64/libsfml-window.so /usr/lib64/libshout.so /usr/lib64/libsigc-2.0.so /usr/lib64/libslang.so /usr/lib64/libsmartcols.so /usr/lib64/libsmbclient.so /usr/lib64/libsmbconf.so /usr/lib64/libsmbldap.so /usr/lib64/libsmime3.so /usr/lib64/libsnappy.so /usr/lib64/libsndfile.so /usr/lib64/libsnmp.so /usr/lib64/libsodium.so /usr/lib64/libsoftokn3.so /usr/lib64/libsoup-2.4.so /usr/lib64/libsoup-gnome-2.4.so /usr/lib64/libsoxr-lsr.so /usr/lib64/libsoxr.so /usr/lib64/libspectre.so /usr/lib64/libspeechd.so /usr/lib64/libspeexdsp.so /usr/lib64/libspeex.so /usr/lib64/libspiro.so /usr/lib64/libsqlite3.so /usr/lib64/libssh2.so /usr/lib64/libssh.so /usr/lib64/libssh_threads.so /usr/lib64/libssl3.so /usr/lib64/libssl.so /usr/lib64/libss.so /usr/lib64/libstartup-notification-1.so /usr/lib64/libstdc++.so /usr/lib64/libstd-f5a209a9.so /usr/lib64/libswresample.so /usr/lib64/libswscale.so /usr/lib64/libsyntax_ext-f5a209a9.so /usr/lib64/libsyntax-f5a209a9.so /usr/lib64/libsyntax_pos-f5a209a9.so /usr/lib64/libsysfs.so /usr/lib64/libsystemd.so) \
     <(nm /usr/lib64/libsamba-credentials.so /usr/lib64/libsamba-errors.so /usr/lib64/libsamba-hostconfig.so /usr/lib64/libsamba-passdb.so /usr/lib64/libsamba-policy.so /usr/lib64/libsamba-util.so /usr/lib64/libsamdb.so /usr/lib64/libsamplerate.so /usr/lib64/libsane.so /usr/lib64/libsasl2.so /usr/lib64/libsbc.so /usr/lib64/libschroedinger-1.0.so /usr/lib64/libseccomp.so /usr/lib64/libsecret-1.so /usr/lib64/libserialize-f5a209a9.so /usr/lib64/libsfml-audio.so /usr/lib64/libsfml-graphics.so /usr/lib64/libsfml-network.so /usr/lib64/libsfml-system.so /usr/lib64/libsfml-window.so /usr/lib64/libshout.so /usr/lib64/libsigc-2.0.so /usr/lib64/libslang.so /usr/lib64/libsmartcols.so /usr/lib64/libsmbclient.so /usr/lib64/libsmbconf.so /usr/lib64/libsmbldap.so /usr/lib64/libsmime3.so /usr/lib64/libsnappy.so /usr/lib64/libsndfile.so /usr/lib64/libsnmp.so /usr/lib64/libsodium.so /usr/lib64/libsoftokn3.so /usr/lib64/libsoup-2.4.so /usr/lib64/libsoup-gnome-2.4.so /usr/lib64/libsoxr-lsr.so /usr/lib64/libsoxr.so /usr/lib64/libspectre.so /usr/lib64/libspeechd.so /usr/lib64/libspeexdsp.so /usr/lib64/libspeex.so /usr/lib64/libspiro.so /usr/lib64/libsqlite3.so /usr/lib64/libssh2.so /usr/lib64/libssh.so /usr/lib64/libssh_threads.so /usr/lib64/libssl3.so /usr/lib64/libssl.so /usr/lib64/libss.so /usr/lib64/libstartup-notification-1.so /usr/lib64/libstdc++.so /usr/lib64/libstd-f5a209a9.so /usr/lib64/libswresample.so /usr/lib64/libswscale.so /usr/lib64/libsyntax_ext-f5a209a9.so /usr/lib64/libsyntax-f5a209a9.so /usr/lib64/libsyntax_pos-f5a209a9.so /usr/lib64/libsysfs.so /usr/lib64/libsystemd.so)
check
echo "/usr/lib32: "
diff <(./my_nm /usr/lib32/libsmartcols.so /usr/lib32/libsndfile.so /usr/lib32/libstdc++.so /usr/lib32/libsystemd.so) <(nm /usr/lib32/libsmartcols.so /usr/lib32/libsndfile.so /usr/lib32/libstdc++.so /usr/lib32/libsystemd.so)
check
