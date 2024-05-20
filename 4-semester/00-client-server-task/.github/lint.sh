#!/usr/bin/env bash
mkdir -p build-ninja
cmake -G Ninja -S . -B build-ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON


ERRORS=0
function countError {
    echo "Проверка завершилась с ошибкой."
    (( ERRORS++ ))
}
trap countError ERR

# echo "# cppcheck"
# cppcheck в Ubuntu 20.04 не поддерживает C++17
# cppcheck --enable=warning,performance --error-exitcode=2 --project=build/compile_commands.json include/ methods/ tests/ && echo "OK" || false

CONFIG='
CheckOptions:
    - { key: readability-magic-numbers.IgnoredFloatingPointValues,
        value: "1.0;2.0;3.0;4.0;5.0;6.0;8.0;9.0;10.0;12.0;16.0;24.0;100.0;1000.0;0.5;0.25;0.125;0.1;0.01" }
'

echo "# clang-tidy"
clang-tidy -p build-ninja/ -header-filter=include/.* --config="$CONFIG" --checks='-*,bugprone-*,performance-*,readability-*,-readability-magic-numbers,misc-*' --warnings-as-errors='*,-readability-magic-numbers' tests/* methods/* include/* && echo "OK" || false

echo "# cpplint"
~/.local/bin/cpplint --recursive --filter="-legal/copyright,-build/c++11,-build/c++14,-build/include_subdir" methods/ tests/ include/ && echo "OK" || false

exit $ERRORS