$session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
$session.UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 Edg/105.0.1343.33"
Invoke-WebRequest -UseBasicParsing -Uri "http://172.16.10.10/poweron" `
-Method "POST" `
-WebSession $session `
-Headers @{
"Accept"="text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9"
  "Accept-Encoding"="gzip, deflate"
  "Accept-Language"="zh-TW,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6"
  "Cache-Control"="max-age=0"
  "Origin"="http://172.16.10.10"
  "Referer"="http://172.16.10.10/"
  "Upgrade-Insecure-Requests"="1"
} `
-ContentType "application/x-www-form-urlencoded" `
-Body "rig=on"