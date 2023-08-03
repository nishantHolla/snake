
#!/bin/bash

make debug && \
cd output && \
echo -en "---------------------------\n" && \
./snake $@
