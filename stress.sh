#!/bin/bash
# usage: ./stress.sh [runs_per_case]   (run `make asan tsan` first)
RUNS=${1:-100}
mkdir -p fails && rm -f fails/*

# format: "expect_no_burnout(0/1) args..."
CASES=(
  "1 5 800 200 100 100 5 10 fifo"
  "1 5 800 200 100 100 5 10 edf"
  "1 4 800 200 100 100 5 10 fifo"
  "1 20 1500 100 50 50 5 5 edf"
  "1 50 2000 50 50 50 5 5 fifo"
  "0 5 300 75 50 50 20 10 fifo"
  "0 5 300 75 50 50 20 10 edf"
  "0 2 100 80 50 50 5 5 edf"
)

run_one() {
  bin=$1; id=$2; expect=$3; shift 3
  out=$(mktemp)
  timeout 30 "$bin" "$@" >"$out" 2>&1
  rc=$?
  reason=""
  if   [ $rc -eq 124 ]; then reason="HANG"
  elif [ $rc -ge 128 ]; then reason="CRASH(rc=$rc)"
  elif grep -qE "Sanitizer|runtime error|data race" "$out"; then reason="SANITIZER"
  elif [ "$expect" = 1 ] && grep -q "burned out" "$out"; then reason="UNEXPECTED_BURNOUT"
  fi
  if [ -n "$reason" ]; then
    f="fails/$(basename $bin)_$id.txt"
    { echo "# $reason: $bin $*"; cat "$out"; } > "$f"
    echo "FAIL $reason  $bin $*"
  fi
  rm -f "$out"
}
export -f run_one

for bin in ./codexion_asan ./codexion_tsan; do
  i=0
  for c in "${CASES[@]}"; do
    for _ in $(seq "$RUNS"); do
      i=$((i+1))
      printf '%s\0%s\0%s\0' "$bin" "$i" "$c"
    done
  done
done | xargs -0 -n3 -P "$(nproc)" bash -c 'run_one $0 $1 $2' 

echo "done. failures: $(ls fails | wc -l) (see fails/)"

