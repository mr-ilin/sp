#! /usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

function _log()
{
  local type=$1
  local message=$2
  local date=$(date +"%Y-%m-%d %H:%M:%S")
  echo "[${date}] [${type}] ${message}"
}

function log_info()
{
  local message=$1
  _log "INFO" "${message}"
}

function log_error()
{
  local message=$1
  _log "ERROR" "${message}"
}

function main()
{
  exe="sp_cp_01"
  run_type=$3

  make clean
  if [ ${run_type} = "debug" ]; then
    log_info "debug..."
    make debug
  else
    make all
  fi

  ./${exe} < $1 > $2
}

main $@
