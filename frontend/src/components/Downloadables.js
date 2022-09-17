import React from 'react';
import { Client } from 'rpc-websockets';
import { Box, ProgressBar, Text, StateLabel, Label, Heading, CounterLabel } from '@primer/react';
import Collapsible from 'react-collapsible';

function ProgressPane (props) {
  switch (props.data.value.status) {
    case '_downloading':
      return (<Box sx={{ width: '300px', float: 'right' }}><Text as="p" m={0} sx={{ textAlign: 'center' }} >{props.data.value.log}</Text><ProgressBar progress={props.data.value.progress}/></Box>);

    case '_completed':
      return (<StateLabel status="issueClosed" sx={{ float: 'right', backgroundColor: 'success.emphasis' }}>Downloaded</StateLabel>);
    case '_skipped':
      return (<StateLabel status="issueClosed" sx={{ float: 'right' }}>Skipped</StateLabel>);

    default:
      return (<></>);
  }
}

function Downloadable (props) {
  return (<Box borderColor="border.default" borderWidth={1} borderStyle="solid" p={4} key={props.data.key}>
      <Text as="span" fontWeight="bold" mx={2}>{props.data.value.data.name}</Text>

      <ProgressPane data={props.data}/>
      <br/>
      <Label size="large">{props.data.plugin}</Label>
    </Box>);
}

function ContainerHeader (props) {
  return <Box borderTopLeftRadius={10} borderTopRightRadius={10} borderColor="border.default" borderWidth={1} borderStyle="solid" mx={4} p={2} backgroundColor="canvas.inset">
    <Text fontWeight="bold">{props.children}</Text></Box>;
}

function DownloadableContainer (props) {
  const ds = props.data;
  const content = (ds.length !== 0)
    ? ds.map(d => (<Downloadable data={d} key={d.key} />))
    : (<Box borderColor="border.default" borderWidth={1} borderStyle="solid" p={4} key={props.data.key}>
  <Text as="span" fontWeight="bold" mx={2}>There are no items to show</Text></Box>);
  return (<Box my={4}>

   <Collapsible trigger={(<ContainerHeader>{props.title} <CounterLabel>{ds.length}</CounterLabel></ContainerHeader>)} triggerStyle={{ marginBottom: 2 }}>
    <Box mx={4}>
    {content}
    </Box>
    </Collapsible>
  </Box>);
}

class Downloadables extends React.Component {
  tick = null;
  state = { data: [] };
  client = null;

  componentDidMount () {
    this.client = new Client('ws://localhost:9090/rpc');
    this.tick = setInterval(
      async () => {
        const r = await this.client.call('get_jobs');
        this.setState({ data: r });
      }
      , 500);
  } // End componentDidMount

  componentWillUnmont () {
    clearInterval(this.tick);
  }

  render () {
    return (<>
<Box borderColor="border.default" borderWidth={1} borderStyle="solid" p={4} mx={8}>
  <Heading>Downloadables & Queue</Heading>
      <DownloadableContainer key="queue" title="Queued" data={this.state.data.filter(d => d.value.status === '_unprocessed')}/>
      <DownloadableContainer key="curr" title="Currently Downloading" data={this.state.data.filter(d => d.value.status === '_downloading')}/>
      <DownloadableContainer key="comp" title="Completed" data={this.state.data.filter(d => d.value.status === '_completed' || d.value.status === '_skipped')}/>
      <DownloadableContainer key="fail" title="Failed" data={this.state.data.filter(d => d.value.status === 'failed')}/>
      </Box>
      </>
    );
  }
} // End class

export default Downloadables;
