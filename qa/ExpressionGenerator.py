import random
import os

INT32_MIN = -2**31
INT32_MAX =  2**31-1

class ExpressionGenerator:
  def generateExpression(size):
    numbers = []
    signs   = []
    for _ in range(size):
      type = random.randint(1,2)
      if   type == 1: numbers.append(random.randint(0,INT32_MAX)) # Integer
      elif type == 2: numbers.append(random.randint(0,INT32_MAX) + random.random()) # Floating point
      else: assert False
    for _ in range(size-1):
      signType = random.randint(1,4)
      if   signType == 1: sign = '+'
      elif signType == 2: sign = '-'
      elif signType == 3: sign = '*'
      elif signType == 4: sign = '/'
      else: assert False
      signs.append(sign)
    expression = ""
    for number,sign in zip(numbers,signs):
      expression += str(number)
      expression += sign
    expression += str(numbers[-1])
    return expression

  def generateFile(fileName, count):
    file = open(fileName, "w")
    file.write(str(count) + '\n')
    for i in range(count):
      size = random.randint(1,7)
      expression = ExpressionGenerator.generateExpression(size)
      try: result = eval(expression)
      except ZeroDivisionError as ex:
        i -= 1
        continue
      file.write(expression + ' ' + str(result) + '\n')
    file.close()
    pass


fileName = "rec/TestExpressions.txt"
count    = 100

if not os.path.exists(fileName.split("/")[0]): os.mkdir(fileName.split("/")[0])
ExpressionGenerator.generateFile(fileName, count)

