int MonitorActivate(){
	error_monitor_lock = buffer_monitor_lock = 1;
}
int MonitorDisable(){
	error_monitor_lock = buffer_monitor_lock = 0;
}
int MonitorGetNumber(){
	return error_monitor_lock + buffer_monitor_lock;
}
