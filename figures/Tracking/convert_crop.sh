#!/bin/sh
epstopdf "$1.eps"
pdfcrop --margins 1 "$1.pdf" "$1.pdf"
