import * as React from 'react';

import { Box, FormControl, TextInput, Button, Label } from '@primer/react';
import { Client } from 'rpc-websockets';

export default class ConfigRow extends React.Component {
  constructor (props) {
    super(props);
    this.state = { value: props.value };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleRemoveConf = this.handleRemoveConf.bind(this);
  }

  shouldComponentUpdate(nextProps, nextState){
    return false;
  }

  handleChange (event) {
    this.setState({ value: event.target.value });
  }

  async handleSubmit (event) {
    event.preventDefault();
    const client = new Client('ws://127.0.0.1:8080/rpc');
    while (!client.ready) {
      await new Promise({ resolve: r => setTimeout(r, 250) });
    }
    client.call(
      this.props.secret ? 'set_secret' : 'set_config',
      {
        key: this.props.k,
        value: this.state.value,
        plugin: this.props.plugin
      }).then(() => window.location.reload(false));
  }

  async handleRemoveConf (event) {
    event.preventDefault();
    const client = new Client('ws://127.0.0.1:8080/rpc');
    while (!client.ready) {
      await new Promise({ resolve: r => setTimeout(r, 250) });
    }
    client.call(
      this.props.secret ? 'set_secret' : 'set_config',
      {
        key: this.props.k,
        value: '',
        plugin: this.props.plugin
      }).then(() => window.location.reload(false));
  }

  render () {
    let b = <></>;
    if (this.props.is_set) {
      b = <Button type="submit">Update</Button>;
    } else {
      b = <Button type="submit" variant="outline">Set</Button>;
    }
    return (
      <Box
        borderColor="border.default" borderWidth={1} borderStyle="solid"
        p={3}
      >

        <form onSubmit={this.handleSubmit}>
          <FormControl>
            <FormControl.Label>{this.props.k} {this.props.req ? <Label>Required</Label> : <></>}</FormControl.Label>
            <TextInput value={this.state.value} onChange={this.handleChange} type={this.props.secret ? 'password' : 'text'} />
            {b} <Button variant="danger" onClick={this.handleRemoveConf}>Delete Value</Button>
          </FormControl>
        </form>
      </Box>
    );
  }
}
