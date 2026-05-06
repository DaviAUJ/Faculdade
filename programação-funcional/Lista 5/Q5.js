const { composite, log, range, sum, equals, indef } = require('./utils.js')

const nums = range(1,1000)

const multiplos = nums.filter(
    (item) => item % 3 === 0 || item % 5 === 0
)

log(
    multiplos.reduce(
        (acc, item) => acc + item
    )
)
