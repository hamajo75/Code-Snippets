#!/bin/bash
SESSION="AP_test"
# new session
tmux new-session -d -s ${SESSION}
# create 2 x 4 panes
tmux split-window -h -t ${SESSION}:0
tmux split-window -h -t ${SESSION}:0
tmux select-pane -t 0
tmux split-window -h -t ${SESSION}:0
tmux select-pane -t 0
tmux split-window -v -t ${SESSION}:0
tmux select-pane -t 2
tmux split-window -v -t ${SESSION}:0
tmux select-pane -t 4
tmux split-window -v -t ${SESSION}:0
tmux select-pane -t 6
tmux split-window -v -t ${SESSION}:0
# start an iperf3-server inside each pane with specified ports
PORTS=( 5501 5502 )
pane=0
for port in "${PORTS[@]}"; do
  tmux select-pane -t ${pane}
  tmux send-keys -t ${SESSION}:0 "iperf3 -s -p ${port} | tee log_${port}.txt" C-m
  pane=$((pane+1))
done