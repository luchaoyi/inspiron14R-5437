#coding:utf8
import csv

#以字典方式写
def demo_dict_write():
    with open('names.csv', 'w') as csvfile:
        fieldnames = ['first_name', 'last_name'] #设置列名
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    
        writer.writeheader()
        writer.writerow({'first_name': 'Baked', 'last_name': 'Beans'})
        writer.writerow({'first_name': 'Lovely', 'last_name': 'Spam'})
        writer.writerow({'first_name': 'Wonderful', 'last_name': 'Spam'})

def demo_dict_read():
    with open('names.csv') as csvfile:
        reader = csv.DictReader(csvfile)
        print reader.fieldnames
        
        for row in reader:
            print row
            #print(row['first_name'], row['last_name'])    
        
            
            
def csv_read():
    with open('names.csv', 'rb') as f:        # 采用b的方式处理可以省去很多问题
        reader = csv.reader(f)
        for row in reader:
            print row
    
def csv_write():
    csv_list=[['first_name', 'last_name'],
    ['Baked', 'Beans'],
    ['Lovely', 'Spam'],
    ['Wonderful', 'Spam']]
    
    with open('some.csv', 'wb') as f:      # 采用b的方式处理可以省去很多问题
        writer=csv.writer(f)
        writer.writerows(csv_list)    
        
    

demo_dict_write() 
demo_dict_read()
csv_read()
csv_write()
