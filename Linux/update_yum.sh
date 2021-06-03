

# solve "No module named rpm" or "rpm/_rpm.so: undefined symbol: rpm"
# Daniel

\rm -rf tmp_rpm
mkdir tmp_rpm
cd tmp_rpm
rpm -qa | grep python | xargs rpm -ev --allmatches --nodeps
whereis python  | xargs rm -frv
rpm -qa | grep yum | xargs rpm -ev --allmatches --nodeps
whereis yum  | xargs rm -frv

\rm *.rpm

wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/libxml2-python-2.9.1-6.el7.5.x86_64.rpm
wget http://rpmfind.net/linux/atrpms/el4-x86_64/atrpms/bleeding/librpm4.3-4.3.3-8_42.el4.at.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/rpm-build-4.11.3-45.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/rpm-build-libs-4.11.3-45.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/rpm-libs-4.11.3-45.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/rpm-sign-4.11.3-45.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/rpm-python-4.11.3-45.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/dbus-python-devel-1.1.1-9.el7.x86_64.rpm

wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-pycurl-7.19.0-19.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-setuptools-0.9.8-7.el7.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-urlgrabber-3.10-10.el7.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-iniparse-0.4-9.el7.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-backports-1.0-8.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-backports-ssl_match_hostname-3.5.0.1-1.el7.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-ipaddress-1.0.16-2.el7.noarch.rpm

wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-kitchen-1.1.1-5.el7.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/yum-metadata-parser-1.1.4-10.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/yum-utils-1.1.31-54.el7_8.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/yum-plugin-fastestmirror-1.1.31-54.el7_8.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/yum-plugin-protectbase-1.1.31-54.el7_8.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/yum-plugin-aliases-1.1.31-54.el7_8.noarch.rpm

wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/yum-3.4.3-168.el7.centos.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-virtualenv-15.1.0-4.el7_7.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/os/x86_64/Packages/python-chardet-2.2.1-3.el7.noarch.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/updates/x86_64/Packages/python-libs-2.7.5-90.el7.x86_64.rpm
wget http://rpmfind.net/linux/centos/7.9.2009/updates/x86_64/Packages/python-2.7.5-90.el7.x86_64.rpm

rpm -Uvh --force --nodeps --replacepkgs *.rpm