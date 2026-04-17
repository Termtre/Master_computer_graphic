git clone --recurse-submodules https://github.com/Termtre/Master_computer_graphic.git

## Windows
.\vcpkg\bootstrap-vcpkg.bat

.\vcpkg integrate cmake

cd lab1

..\vcpkg\vcpkg install

## Unix

./vcpkg/bootstrap-vcpkg.sh
./vcpkg integrate cmake

cd lab1

..\vcpkg\vcpkg install
