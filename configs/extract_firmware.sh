#!/sbin/sh

for file in /firmware/image/*.gz; do
  OUT_FILE=$(basename $file .gz)
  gzip -dc $file > /system/vendor/firmware/$OUT_FILE
  chmod 644 /system/vendor/firmware/$OUT_FILE
  chcon u:object_r:firmware_file:s0 /system/vendor/firmware/$OUT_FILE
done
