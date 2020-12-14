
int treecount(root)
{
	if(root==NULL) return 0;
	return treecount(root->left)+treecount(root->right)+1;
}

int height(root)
{
	int u,v;
	if(root==NULL) return -1;
	u=height(root->left);
	v=height(root->right);
	
	if(u>v) return u+1;
	else return v+1;
}
