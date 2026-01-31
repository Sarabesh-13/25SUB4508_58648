#!/bin/bash
: ' script for declaring for local and environment variable and displaying it and show which'

local="I am local to parent script"

export env_var="I am environment variable"

echo "parent script"
echo "local variable $local"
echo "env variable $env_var"
echo "===================="

echo
echo "Calling child script"
./child.sh