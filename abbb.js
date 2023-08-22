const print = (str) => console.log(str)

const listSum = (list) => list.reduce( (acc, x) => acc + x )

module.exports = { print, listSum }