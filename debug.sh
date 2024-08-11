
#!/bin/bash

mkdir -p out
cp -rv assets/* out
make debug && \
cd out && \
echo -en "---------------------------\n" && \
./snake $@
