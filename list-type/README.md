Step of building
-----
```bash
make
```
	hello-list.ko will be compiled.
## insert module to kernel module list
	insmod hello-list.ko
## remove module from kernel.
	rmmod hello-list.ko
## kernel message
```bash
cat /proc/kmsg

<4>[16377.872965] Module, hello list init.
<4>[16377.872968] Module, hello list.
<4>[16377.872969] list_add node_1,2,3,4
<4>[16377.872969] list-name: node3
<4>[16377.872970] list-id: 3
<4>[16377.872971] list-name: node2
<4>[16377.872972] list-id: 2
<4>[16377.872973] list-name: node1
<4>[16377.872973] list-id: 1
<4>[16377.872974] list-name: node4
<4>[16377.872975] list-id: 4
<4>[16377.872975] after list_move node_3
<4>[16377.872976] list-name: node2
<4>[16377.872977] list-id: 2
<4>[16377.872977] list-name: node1
<4>[16377.872978] list-id: 1
<4>[16377.872979] list-name: node4
<4>[16377.872979] list-id: 4
<4>[16377.872980] head2 list node
<4>[16377.872981] list-name: node3
<4>[16377.872981] list-id: 3
<4>[16377.872982] after list_move_tail node_4
<4>[16377.872983] list-name: node2
<4>[16377.872983] list-id: 2
<4>[16377.872984] list-name: node1
<4>[16377.872985] list-id: 1
<4>[16377.872985] head2 list node
<4>[16377.872986] list-name: node3
<4>[16377.872987] list-id: 3
<4>[16377.872987] list-name: node4
<4>[16377.872988] list-id: 4
<4>[16377.872989] after list_del node_1
<4>[16377.872989] list-name: node2
<4>[16377.872990] list-id: 2
<4>[16377.872991] after list_del node_2
<4>[16377.872991] head2  after list_del node_4
<4>[16377.872992] list-name: node3
<4>[16377.872993] list-id: 3
<4>[16377.872993] after list_del node_3
<4>[16377.872994] Module, hello hlist.
<4>[16377.872995] list_add node_1,2,3,4
<4>[16377.872995] hlist-name: node4
<4>[16377.872996] hlist-id: 4
<4>[16377.872997] hlist-name: node3
<4>[16377.872997] hlist-id: 3
<4>[16377.872998] hlist-name: node2
<4>[16377.872999] hlist-id: 2
<4>[16377.872999] hlist-name: node1
<4>[16377.873000] hlist-id: 1
<4>[16377.873001] after list_move node_3
<4>[16377.873001] hlist-name: node4
<4>[16377.873002] hlist-id: 4
<4>[16377.873003] hlist-name: node3
<4>[16377.873003] hlist-id: 3
<4>[16377.873004] hlist-name: node2
<4>[16377.873005] hlist-id: 2
<4>[16377.873005] hlist-name: node1
<4>[16377.873006] hlist-id: 1
<4>[16377.873007] head2 list node
<4>[16377.873007] hlist-name: node4
<4>[16377.873008] hlist-id: 4
<4>[16377.873009] hlist-name: node3
<4>[16377.873009] hlist-id: 3
<4>[16377.873010] hlist-name: node2
<4>[16377.873011] hlist-id: 2
<4>[16377.873011] hlist-name: node1
<4>[16377.873012] hlist-id: 1
<4>[16377.873013] after list_del node_1
<4>[16377.873013] hlist-name: node4
<4>[16377.873014] hlist-id: 4
<4>[16377.873015] hlist-name: node3
<4>[16377.873015] hlist-id: 3
<4>[16377.873016] hlist-name: node2
<4>[16377.873017] hlist-id: 2
<4>[16377.873017] after list_del node_2
<4>[16377.873018] hlist-name: node4
<4>[16377.873019] hlist-id: 4
<4>[16377.873019] hlist-name: node3
<4>[16377.873020] hlist-id: 3
<4>[16377.873021] head2  after list_del node_4
<4>[16377.873021] hlist-name: node3
<4>[16377.873022] hlist-id: 3
<4>[16377.873022] after list_del node_3
<4>[16377.873022] Module, hello list exit.
```
