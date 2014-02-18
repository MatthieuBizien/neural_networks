TEMPLATE=subdirs
CONFIG+=ordered
win32 {
SUBDIRS=src
}
!win32 {
SUBDIRS=src tests
}
