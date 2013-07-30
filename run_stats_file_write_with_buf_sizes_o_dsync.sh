declare -a buf_size;
declare -i size;

buf_size=(1 2 4 8 16 32 64 128 256 512 1024 2048 4096 16384 65536);

for size in ${buf_size[@]}
do
  echo "Buffer Size: $size";
  echo "Time:";
  out=$(time ./stats_file_write_with_o_dsync $size);
  echo $out;
done;
