#! /bin/sh

# -- Default settings --
pkgName=""
pkgVersion=""
pkgRevision="r1"
pkgOS=""
pkgArch="`uname -m`"
pkgCompiler=""
pkgSource=""
pkgCompiler="g++"
pkgTarget=""

zip=""
zipFromUser=0
find=""
mktemp=""

targetFolder=`dirname "$0"`


checkEnv()
{
	if [ "x${find}" = "x" -o ! -x "${find}" ]; then
		find=`which find`
		if [ "x${find}" = "x" -o ! -x "${find}" ]; then
			echo "The program 'find' is missing or could not be found. Aborting now."
			exit 3
		fi
	fi
	if [ "x${mktemp}" = "x" -o ! -x "${mktemp}" ]; then
		mktemp=`which mktemp`
		if [ "x${mktemp}" = "x" -o ! -x "${mktemp}" ]; then
			echo "The program 'mktemp' is missing or could not be found. Aborting now."
			exit 3
		fi
	fi
	if [ "x${zip}" = "x" -o ! -x "${zip}" ]; then
		zip=`which zip`
		if [ "x${zip}" = "x" -o ! -x "${zip}" ]; then
			echo "The program 'zip' is missing or could not be found. Aborting now."
			exit 3
		fi
	fi
}


printPkgSettings()
{
	if [ ! "x${pkgName}" = "x" ]; then
		echo " * Package: '${pkgName}'"
	fi
	if [ ! "x${pkgVersion}" = "x" ]; then
		echo " * Version: '${pkgVersion}'"
	fi
	if [ ! "x${pkgRevision}" = "x" ]; then
		echo " * Revision: '${pkgRevision}'"
	fi
	if [ ! "x${pkgOS}" = "x" ]; then
		echo " * OS: '${pkgOS}'"
	fi
	if [ ! "x${pkgArch}" = "x" ]; then
		echo " * Arch: '${pkgArch}'"
	fi
	if [ ! "x${pkgCompiler}" = "x" ]; then
		echo " * Compiler: '${pkgCompiler}'"
	fi
	if [ ! "x${pkgSource}" = "x" ]; then
		echo " * Source: '${pkgSource}'"
	fi
	if [ ! "x${pkgTarget}" = "x" ]; then
		echo " * Source: '${pkgTarget}'"
	fi
	if [ "${zipFromUser}" -eq 1 ]; then
		echo " * zip: '${zip}' (user)"
	else
		echo " * zip: '${zip}' (auto)"
	fi
}


# $1 The folder
checkDevPackFolder()
{
	if [ ! -d "${1}/cmake" ]; then
		echo "[ERROR] Invalid DevPack structure: The folder '${1}/cmake' is missing"
		exit 5
	fi
	if [ ! -d "${1}/${pkgCompiler}" ]; then
		echo "[ERROR] Invalid DevPack structure: The folder '${1}/${pkgCompiler}' is missing"
		exit 5
	fi
	if [ ! -d "${1}/${pkgCompiler}/include" ]; then
		echo "[WARNING] Invalid DevPack structure: The folder '${1}/${pkgCompiler}/include' is missing"
	fi
	if [ ! -d "${1}/${pkgCompiler}/lib/${pkgTarget}" ]; then
		echo "[WARNING] Invalid DevPack structure: The folder '${1}/${pkgCompiler}/lib/${pkgTarget}' is missing"
	fi
}


help()
{
	echo "Yuni - Package maker for externals dependencies"
	echo "Usage: `basename "$0"` [<options>] <sourcedir>"
	echo "Options:"
	echo "   -n  : Name of the package (ex: '-n irrlicht', '-n lua')"
	echo "   -v  : Version of the package (ex: '-v1.4.1')"
	echo "   -r  : Revision for the package (ex: '-r2')"
	echo "   -o  : Operating system (ex: '-o macos', '-o linux', '-o windows)"
	echo "   -a  : Architecture (ex: '-a 386', '-a ppc', '-a ub')"
	echo "   -f  : Target folder for the package"
	echo "   -c  : Compiler (ex: '-c vs9', '-c mingw', '-c g++', '-c g++4.2')"
	echo "   -t  : Target (ex: '-t release', '-t debug')"
	echo "   -z  : The program 'zip' to use to compress (archive) files (ex: '-z/usr/bin/zip')"
	echo "   -h  : This help"
	echo
	echo "Example:"
	echo "  ./makepackage.sh -n irrlicht -v1.4.1 -r3 ~/projects/irrlicht/1.4.1/trunk"
	echo
	echo "Note: The source directory should be like this :"
	echo "  + <the source dir>"
	echo "    |- cmake (.cmake)"
	echo "    |- <compiler> (g++, vs9...)"
	echo "       |- include (.h)"
	echo "       \- lib"
	echo "          |- debug/ (.a,.so,.dll,.lib)"
	echo "          \- release/ (.a,.so,.dll,.lib)"
	echo
	exit 0
}


# -- Auto Detection - OS --
if [ -x "/usr/bin/sw_vers" ]; then
	# OS X
	pkgOS="macos"
else
	linuxRelease=`ls /etc/*-release 2&>/dev/null`
	if [ ! "x${linuxRelease}" = "x" ]; then
		# GNU/Linux
		pkgOS="linux"
	fi
fi



args=`getopt n:v:r:o:c:a:s:z:f:t:h $*`
if [ $? != 0 ]; then
	help
	exit 2
fi
set -- $args
for i
do
	case "$i"
	in
		-h)		help; shift;;
		-n)		pkgName="$2"; shift; shift;;
		-v)		pkgVersion="$2"; shift; shift;;
		-r)		pkgRevision="r$2"; shift; shift;;
		-o)		pkgOS="$2"; shift; shift;;
		-a)		pkgArch="$2"; shift; shift;;
		-c)		pkgCompiler="$2"; shift; shift;;
		-t)		pkgTarget="$2"; shift; shift;;
		-f)		targetFolder="$2"; shift; shift;;
		-z)		zip="$2"; zipFromUser=1; shift; shift;;
        --)		shift; break;;
    esac
done

pkgSource="$*"


checkEnv



#
# Go go go
#

echo "Yuni - Package maker for externals dependencies"
printPkgSettings


good='1'
if [ "x${pkgName}" = "x" ]; then
	echo "[ERROR] The name of the package is missing (ex: '-n irrlicht', '-n lua')"
	good='0'
fi
if [ "x${pkgVersion}" = "x" ]; then
	echo "[ERROR] The version is missing (ex: '-v1.4.1')"
	good='0'
fi
if [ "x${pkgRevision}" = "x" ]; then
	echo "[ERROR] The revision is missing (ex: '-r2')"
	good='0'
fi
if [ "x${pkgOS}" = "x" ]; then
	echo "[ERROR] The operating system is missing (ex: '-o macos', '-o linux', '-o windows')"
	good='0'
fi
if [ "x${pkgArch}" = "x" ]; then
	echo "[ERROR] The architecture is missing (ex: '-a i386', '-a ppc', '-a ub')"
	good='0'
fi
if [ "x${pkgCompiler}" = "x" ]; then
	echo "[ERROR] The compiler is missing (ex: '-c vs9', '-c mingw', '-c g++', '-c g++4.2')"
	good='0'
fi
if [ "x${pkgTarget}" = "x" ]; then
	echo "[ERROR] The target is missing"
	good='0'
fi


if [ "x${pkgSource}" = "x" ]; then
	echo "[ERROR] The source directory is missing"
	good='0'
fi


if [ "${good}" -eq 0 ]; then
	echo "An error has occured. To have more informations please use type ''`basename "$0"` -h''"
	echo "Aborting."
	exit 1
fi


target="${targetFolder}/${pkgName}-${pkgVersion}-${pkgRevision}-${pkgOS}-${pkgArch}-${pkgCompiler}-${pkgTarget}.zip"

echo " * Archive : ${target}"
if [ -f "${target}" ]; then
	echo "The archive file already exists. Aborting."
	exit 1

fi

checkDevPackFolder "${pkgSource}"


devpack="${pkgSource}/yndevpack-${pkgName}-${pkgVersion}-${pkgRevision}-${pkgOS}-${pkgArch}-${pkgCompiler}-${pkgTarget}"
echo 1 > "${devpack}"

tmpfile=`"${mktemp}" -t yunipackagemaker.XXXXXX` || exit 4

# Waht files to include
cd "${pkgSource}" \
	&& echo "Searching files to include into the package..." \
	&& "${find}" . '(' ! -path '*/.*' -and ! -name '*.o' -and ! -name '#*' ')' > "${tmpfile}" \
	&& echo "Creating the archive... Please wait..." \
	&& "${zip}" -n .Z:.zip:.png:.gif:.snd:.mp3:.jpg:.rar:.bz2:.gz -Xyr "${target}" . -i@"${tmpfile}"
result="$?"
if [ "${result}" -eq 0 ]; then
	echo "The package is ready: '${target}'"
else
	echo "[ERROR] An error has occured. Aborting."
fi


# Removing the tmp file
rm -f "${tmpfile}"
if [ -f "${tmpfile}" ]; then
	echo "[WARNING] The temporary file could be removed: '${tmpfile}'"
fi
rm -f "${devpack}"


echo "Done."


