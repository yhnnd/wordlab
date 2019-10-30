string csvQueryShellVersion(){
	return "csv query (build "
	+csvquery::constructorVersion()
	+" / exec "
	+csvquery::executorVersion()
	+")";
}
