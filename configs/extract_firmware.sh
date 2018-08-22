#!/sbin/sh

for file in /firmware/image/*.gz; do
  OUT_FILE=$(basename $file .gz)
  gzip -dc $file > /system/etc/firmware/$OUT_FILE
  chmod 644 /system/etc/firmware/$OUT_FILE
  chmod 644 /system/build.prop
  chcon u:object_r:firmware_file:s0 /system/etc/firmware/$OUT_FILE
done
