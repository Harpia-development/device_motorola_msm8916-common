#!/vendor/bin/sh
#
# Copy qcril.db if needed for RIL
#
if [ -f /vendor/radio/qcril_database/qcril.db -a ! -f /data/vendor/radio/qcril.db ]; then
    cp /vendor/radio/qcril_database/qcril.db /data/vendor/radio/qcril.db
    chown -h radio.radio /data/vendor/radio/qcril.db
fi
echo 1 > /data/vendor/radio/db_check_done

echo 1 > /data/vendor/radio/copy_complete
