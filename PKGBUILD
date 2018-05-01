# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: Michael Kuc <michaelkuc6@gmail.com>
pkgname=dwm
pkgver=6.1
pkgrel=1
pkgdesc="A custom version of dwm modified for my purposes."
arch=('i686' 'x86_64')
url="https://dwm.suckless.org/"
license=('MIT/X Consortium license'/)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'rofi' 'feh')
provides=('dwm')
conflicts=('dwm')
epoch=1
source=("config.def.h"
	"config.mk"
	"drw.c"
	"drw.h"
	"dwm.1"
	"dwm.c"
	"Makefile"
	"transient.c"
	"util.c"
	"util.h"
	"LICENSE"
	"README"
	"dwm.template.desktop")

prepare() {
	cp $srcdir/dwm.template.desktop $srcdir/dwm.desktop
	diresc=$(echo $HOME | sed 's_/_\\/_g')
	sed -i -- "s/\~/$(echo $diresc)/g" $srcdir/dwm.desktop
}

build() {
	make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

check() {
	: #Do nothing
}

package() {
	make PREFIX=/usr DESTDIR="$pkgdir/" install
	install -m644 -D $srcdir/LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
	install -m644 -D $srcdir/README "$pkgdir/usr/share/doc/$pkgname/README"
	install -m644 -D $srcdir/dwm.desktop "$pkgdir/usr/share/xsessions/dwm.desktop"
}

md5sums=(SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP
         SKIP)
