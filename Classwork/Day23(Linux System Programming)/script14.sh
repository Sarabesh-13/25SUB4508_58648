#!/bin/bash
: 'check a user logged in status'

status=$(last $USER | grep "logged in")

if [ $? -eq 0 ]; then
  echo "logged_in_status:$status"
else
  echo "logged_in_status:not active"
fi