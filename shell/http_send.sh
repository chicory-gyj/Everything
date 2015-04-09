for i in {1..100}
do
    curl --data "sessionId=955cc6cf8ff73e96&mac=90%3Afd%3A61%3A84%3Ad4%3Aec&auth_status=1&username=yan&sessionTimeout=12" http://10.50.120.68/outservice/authManager/notice
done
