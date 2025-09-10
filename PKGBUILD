pkgname=streampipes-git
pkgver=r0.0.0
pkgrel=1
pkgdesc="User-space pseudo device files that simulate real-time streams"
arch=('x86_64')
url="https://github.com/szmelc/StreamPipes"
license=('MIT')
depends=('fuse3')
makedepends=('git' 'make' 'gcc' 'pkg-config')
provides=('streampipes')
source=("$pkgname::git+https://github.com/szmelc/StreamPipes.git")
sha256sums=('SKIP')

pkgver() {
  cd "$srcdir/$pkgname"
  echo r$(git rev-list --count HEAD).$(git rev-parse --short HEAD)
}

build() {
  cd "$srcdir/$pkgname"
  make
}

package() {
  cd "$srcdir/$pkgname"
  make DESTDIR="$pkgdir" PREFIX=/usr install
}
