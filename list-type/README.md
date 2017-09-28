Step of building
-----
```bash
make
```
	hello-list.ko will be compiled.
## insert module to kernel module list
	insmod hello-list.ko
## remove module from kernel.
	rmmod hello.ko
## kernel message
```bash
cat /proc/kmsg

<3>[95073.972252] Module, hello list init.
<4>[95073.972643] list_add node_1,2,3,4
<4>[95073.972645] name: node3
<4>[95073.972646] id: 3
<4>[95073.972647] name: node2
<4>[95073.972648] id: 2
<4>[95073.972648] name: node1
<4>[95073.972649] id: 1
<4>[95073.972650] name: node4
<4>[95073.972651] id: 4
<4>[95073.972652] after list_move node_3
<4>[95073.972652] name: node2
<4>[95073.972653] id: 2
<4>[95073.972654] name: node1
<4>[95073.972655] id: 1
<4>[95073.972656] name: node4
<4>[95073.972656] id: 4
<4>[95073.972657] head2 list node
<4>[95073.972658] name: node3
<4>[95073.972659] id: 3
<4>[95073.972660] after list_movei_tail node_4
<4>[95073.972661] name: node2
<4>[95073.972661] id: 2
<4>[95073.972662] name: node1
<4>[95073.972663] id: 1
<4>[95073.972664] head2 list node
<4>[95073.972665] name: node3
<4>[95073.972666] id: 3
<4>[95073.972667] name: node4
<4>[95073.972668] id: 4
<4>[95073.972668] after list_del node_1
<4>[95073.972669] name: node2
<4>[95073.972670] id: 2
<4>[95073.972671] after list_del node_2
<4>[95073.972672] head2  after list_del node_4
<4>[95073.972673] name: node3
<4>[95073.972674] id: 3
<4>[95073.972674] after list_del node_3
<3>[95076.102687] Module, hello list exit.
```
