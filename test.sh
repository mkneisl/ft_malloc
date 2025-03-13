#/bin/bash

if [ "$(uname)" = 'Linux' ]
then
	export LD_LIBRARY_PATH=.
	export LD_PRELOAD=libft_malloc.so
else
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES=libft_malloc.so
	export DYLD_FORCE_FLAT_NAMESPACE=1
fi

$@

if [ "$(uname)" = 'Linux' ]
then
	unset LD_LIBRARY_PATH
	unset LD_PRELOAD
else
	unset DYLD_LIBRARY_PATH
	unset DYLD_INSERT_LIBRARIES
	unset DYLD_FORCE_FLAT_NAMESPACE
fi
