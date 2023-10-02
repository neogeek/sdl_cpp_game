#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    cd "${SCRIPT_DIR}" || exit

    cd ..

    find images -type f -name "*.png" -exec sh -c 'xxd -i "$0" "${0%.png}.h"' {} \;
    find fonts -type f -name "*.ttf" -exec sh -c 'xxd -i "$0" "${0%.ttf}.h"' {} \;

)
