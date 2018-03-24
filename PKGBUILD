# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: Your Name <youremail@domain.com>
pkgname=dwm
pkgver=6.1
pkgrel=1
pkgdesc="A custom version of dwm modified for my purposes."
arch=('i686' 'x86_64')
url="https://dwm.suckless.org/"
license=('MIT/X Consortium license'/)
groups=()
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'st' 'dmenu')
provides=("dwm")
install=
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
	"dwm.desktop")

prepare() {
	: #Do nothing
}

build() {
	make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

check() {
	: #Do nothing
}

package() {
	make DESTDIR="$pkgdir/" install
	install -m644 -D $srcdir/LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
	install -m644 -D $srcdir/README $pkgdir/usr/share/doc/$pkgname/README
	install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}

md5sums=('3e0e53c181f5c536cc88c5a7cc552e87'
         'ef1dfdc3b7120d2f82194f54ef0cea93'
         '8742b0e99c633724a73dcff43e521380'
         '2170b6fe645068a2cad4be60d5ebbd84'
         '6356eb6e663c273b6bc8e00cdd3799ef'
         'ac27c599a8430d004d5484e602529c3e'
         '62489d2f9bdd33597d34ed2b8c85f1cf'
         '1f002e4c3da39eed17c5581e8649daa1'
         'e1d877b57636568ba579b1bc0ae42e8f'
         '007c065ca60e3f3c56bf153f2f769a90'
         '8555b535ebdcbd0f153d5c9fabde7168'
         'ad7413999e5ed8abc7747e52ec870a0f'
         '73be62f9b238c1c96f8e7542908691a3')
