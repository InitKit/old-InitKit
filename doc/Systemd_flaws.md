Notes towards a technical critique of SystemD
=============================================

This work-in-progress document collects brief notes which will form the basis of
an article demonstrating the bankruptcy of SystemD's architecture and the need
to abandon this app at once.

Too Clever By Half
------------------

The SystemD developers misinterpreted the Unix Philosophy (which is really about
object-oriented programming, particularly using file descriptors as a universal
object) as meaning "you have to abuse the filesystem, using its layout to store
data."

Symlinks are the worst-abused feature here. SystemD makes symlinks significant.
Some who would falsely accuse System V RC of making symlinks significant must be
corrected, for System V RC does not make symlinks significant - it does not use
`readlink` nor `O_NOFOLLOW` to traverse the symlink. The test here is whether
you can replace the symlink with a copy of the file and get the same result.
SystemD miserably fails this test; instead of sensibly asking users to
create (for example) explicit 'alias' service files, or asking them to add alias
names to the service file, it uses symlinks, sowing confusion and creating all
manner of problems.

The Unix filesystem is a pleasant and straightforward graph; symlinks introduce
all manner of confusion, and to derive actual *meaning* from them is a terrible
thing, and illustrates a cavalier attitude in the X Desktop Group where
complicatedness is sought instead of shunned.