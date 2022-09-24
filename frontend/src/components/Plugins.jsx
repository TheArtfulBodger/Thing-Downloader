import React from 'react';
import { Client } from 'rpc-websockets';
import { Label, Button, Box, Text } from '@primer/react';
import { GearIcon, DesktopDownloadIcon } from '@primer/octicons-react';
import { toast } from 'react-toastify';

import { curry } from 'lodash';
import RpcComponent from '../RPCComponent';

export async function LoadJobs (key, client, event) {
  const rsp = await client.call('load_jobs', { plugin: key });
  if (rsp.success) {
    toast.success('Successfully Queued Jobs');
  } else {
    toast.error('Hello');
  }
}

function Plugin ({ data: [key, data], rpc }) {
  let c = <></>;
  if (!data.has_required_confs) {
    c = <Label variant='danger' >Missing Required Configuration</Label>;
  }

  let s = <></>;
  if (!data.has_required_secrets) {
    s = <Label variant='danger' >Missing Required Secrets</Label>;
  }

  return (<Box
    display="flex" alignItems="center" justifyContent="space-between"
    borderColor="border.default" borderWidth={1} borderStyle="solid"
    p={4} key={key}
          >
    <Box maxWidth="50%">
      <Text as="p" fontWeight="bold">{data.name}</Text>
      <Text as="p">{data.description}</Text>

      <Label size="large">{key}</Label>
    </Box>
    <Box display="grid" gridTemplateColumns="1fr 1fr" gridGap={1}>
      <Box>
        {c}{s}
      </Box>
      <Box>
        <Button
          sx={{ float: 'right' }} leadingIcon={GearIcon} as="a"
          href={`/plugins/configuration?plugin=${key}#config`}
        >Configuration</Button>
      </Box>
      <Box />
      <Box>
        <Button
          key={key} sx={{ float: 'right' }} onClick={curry(LoadJobs)(key, rpc)}
          variant="outline" leadingIcon={DesktopDownloadIcon} disabled={!(data.has_required_confs && data.has_required_secrets)}
        >Load Jobs</Button>
      </Box>
    </Box>
  </Box>);
}

export default class PluginList extends RpcComponent([["get_plugins", "plugins"]]) {
  tick = null;
  state = { plugins: [] };
  client = null;

  render () {
    const ds = this.state.plugins.loaded;
    if (ds === undefined) { return <></>; }
    const content = Object.entries(ds).map(d => (<Plugin key={d[0]} data={d} rpc={this.client} />));

    return (<>
      <Box my={4}>
        <Box>
          {content}
        </Box>
      </Box>
    </>);
  }
}
