#!/bin/bash
while true; do
./r > input //��������¼�
./a < input > output.a
./b < input > output.b
diff output.a output.b //�ı��Ƚ�
if [ $? -ne 0 ] ; then break;fi //�жϷ���ֵ
done